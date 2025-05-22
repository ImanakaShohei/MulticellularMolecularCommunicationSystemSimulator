import glob
import matplotlib.animation as animation
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib import colormaps as cmaps
import cv2
import numpy as np
import glob
import math
import os

cell_files = sorted(glob.glob('./result/*'))
molecule_files = sorted(glob.glob("molecule_result/0/molecule_*"))

if not os.path.exists("./image"):
    os.mkdir("./image")

with open('config.txt', 'r') as f:
    img_w_len = int(f.readline())
    img_h_len = int(f.readline())
    step_num = int(f.readline())
    time_per_file = float(f.readline())

IMAGE_LEN = 1024

time_delta_sec = time_per_file * 60
scale = IMAGE_LEN / img_w_len
cmap = cmaps.get_cmap('Reds')

for i in range(len(cell_files)):
    has_molecule = False

    img = np.full((IMAGE_LEN, IMAGE_LEN, 3), 255, dtype=np.uint8)

    fig, ax = plt.subplots(figsize=(1, 1), dpi=20)

    deg3 = []
    with open(molecule_files[i], "r") as f:
        field3D = f.readlines()

        for field_surface in field3D:
            deg2 = []
            field_lines = field_surface.split("|")[:-1]

            for line in field_lines:
                has_molecule = True
                elements = list(map(float, line.split(" ")[:-1]))

                deg2.append(elements)

            deg3.append(deg2)

    if has_molecule:
        XY = np.array(deg3).squeeze().T

        XY = np.array(XY, dtype=np.uint32)
        color_img = np.array(cmap(XY*100, bytes=True), dtype=np.uint8)

        color_img = cv2.cvtColor(color_img, cv2.COLOR_RGBA2BGR)

        height, width, channels = color_img.shape

        zoomed_color_img = cv2.resize(color_img, None, fx=IMAGE_LEN/width, fy=IMAGE_LEN/height, interpolation=cv2.INTER_NEAREST)
        img = zoomed_color_img

    cv2.circle(img, (IMAGE_LEN//2, IMAGE_LEN//2), IMAGE_LEN//2, (0, 0, 0))
    cv2.line(img, (0, IMAGE_LEN//2), (IMAGE_LEN, IMAGE_LEN//2), (0, 0, 0))
    cv2.line(img, (IMAGE_LEN//2, 0), (IMAGE_LEN//2, IMAGE_LEN), (0, 0, 0))

    with open(cell_files[i], 'r') as f:
        cells = f.read().split('\n')

    cell_objs = []

    # cell[id, typeID, x, y, z, vx, vy, vz, r, contact num, contact id...]
    for cell in cells[1:-1]:
        cell = cell.split('\t')
        cell_id = int(cell[0])
        cell_type = cell[1]
        x = float(cell[2])*scale+IMAGE_LEN/2
        y = float(cell[3])*scale+IMAGE_LEN/2
        z = float(cell[4])*scale+IMAGE_LEN/2
        r = float(cell[8])*scale
        adhere_cells_str = cell[10]

        cell_objs.append((cell_id, cell_type, x, y, r, adhere_cells_str))

        if x < 0 or x > IMAGE_LEN or y < 0 or y > IMAGE_LEN:
            print('out of range')

        if cell_type == 'WORKER':
            cell_color = (0, 200, 0)
        elif cell_type == 'DEAD':
            cell_color = (0, 0, 0)
        elif cell_type == 'NONE':
            continue

        cv2.circle(img, (math.floor(x), math.floor(y)),
                   math.floor(r), cell_color, thickness=1)

    for cell_obj in cell_objs:
        adhere_list = cell_obj[5].split(',')
        for adhere_id in adhere_list:
            if adhere_id == '_':
                continue
            adhere_id = int(adhere_id)
            
            # 二重に描画するのを防ぐ
            if adhere_id < cell_obj[0]:
                continue

            # adhere_idのCellがあるindexを探す
            adhere_index = 0
            while cell_objs[adhere_index][0] != adhere_id:
                adhere_index += 1
            
            adhere_obj = cell_objs[adhere_index]
            x1 = cell_obj[2]
            y1 = cell_obj[3]
            x2 = adhere_obj[2]
            y2 = adhere_obj[3]
            cv2.line(img, (math.floor(x1), math.floor(y1)),
                     (math.floor(x2), math.floor(y2)), (0, 0, 255), thickness=1)

    path = f'./image/cells_{cell_files[i][-5:]}.png'
    is_ok = cv2.imwrite(path, img)  # FIXME: 色がおかしいので、修正する。

    print(f'{path} : {is_ok}')

exit()
