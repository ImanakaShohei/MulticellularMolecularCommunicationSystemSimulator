#include "SimulationSettings.hpp"

/**
 * @brief 設定ファイルからの読み込み
 * @brief 必要に応じてユーザが設定項目を書き足しても良い。
 * @note 設定ファイルのパスはsrc/config.yaml。パースに失敗した場合は例外処理をする。
 *
 * @return true
 * @return false
 */
bool SimulationSettings::init_settings()
{
    std::string path = "src/config.yaml";

    try {
        YAML::Node config = YAML::LoadFile(path);

        auto&& cellNode = config["cell"];

        CELL_SEED = cellNode["cell_seed"].as<int32_t>();
        CELL_NUM  = cellNode["cell_num"].as<int32_t>();
        assert(CELL_NUM >= 0);

        std::string postionUpdateMethodStr = cellNode["position_update_method"].as<std::string>();
        if (postionUpdateMethodStr == "AB4")
            POSITION_UPDATE_METHOD = PositionUpdateMethod::AB4;
        else if (postionUpdateMethodStr == "AB3")
            POSITION_UPDATE_METHOD = PositionUpdateMethod::AB3;
        else if (postionUpdateMethodStr == "AB2")
            POSITION_UPDATE_METHOD = PositionUpdateMethod::AB2;
        else if (postionUpdateMethodStr == "EULER")
            POSITION_UPDATE_METHOD = PositionUpdateMethod::EULER;
        else if (postionUpdateMethodStr == "ORIGINAL")
            POSITION_UPDATE_METHOD = PositionUpdateMethod::ORIGINAL;
        else {
            std::cerr << "Invalid position_update_method: " << postionUpdateMethodStr << std::endl;
            return false;
        }

        auto&& simulationNode = config["simulation"];

        SIM_STEP = simulationNode["sim_step"].as<int32_t>();
        assert(SIM_STEP >= 0);
        OUTPUT_INTERVAL_STEP = simulationNode["output_interval"].as<int32_t>();
        assert(OUTPUT_INTERVAL_STEP > 0);
        FIELD_X_LEN = simulationNode["field_x_len"].as<int32_t>();
        assert(FIELD_X_LEN >= 0);
        FIELD_Y_LEN = simulationNode["field_y_len"].as<int32_t>();
        assert(FIELD_Y_LEN >= 0);
        FIELD_Z_LEN = simulationNode["field_z_len"].as<int32_t>();
        assert(FIELD_Z_LEN >= 0);
        DELTA_TIME = simulationNode["delta_time"].as<double>();
        assert(DELTA_TIME > 0.0);

        auto algorithmsTypeStr = simulationNode["algorithm_type"].as<::std::string>();

        if (algorithmsTypeStr == "NAIVE") ALGORITHM_TYPE = AlgorithmType::Naive;
        else if (algorithmsTypeStr == "CELL-LIST") ALGORITHM_TYPE = AlgorithmType::CellList;
        else if (algorithmsTypeStr == "BARNES-HUT") ALGORITHM_TYPE = AlgorithmType::BarnesHut;
        else if (algorithmsTypeStr == "CLUSTER") ALGORITHM_TYPE = AlgorithmType::Cluster;
        else [[unlikely]] {
            std::cerr << "Invalid algorithm_type: " << postionUpdateMethodStr << std::endl;
            return false;
        }

        auto&& moleculeNode = config["molecule"];

        DEFAULT_MOLECULE_NUMS = moleculeNode["default_molecule_nums"].as<std::vector<int64_t>>();
        assert(DEFAULT_MOLECULE_NUMS.size() > 0);
        MOLECULE_TYPE_NUM    = DEFAULT_MOLECULE_NUMS.size();
        MOLECULE_FIELD_X_LEN = moleculeNode["field_x_len"].as<int32_t>();
        assert(MOLECULE_FIELD_X_LEN >= 1);
        MOLECULE_FIELD_Y_LEN = moleculeNode["field_y_len"].as<int32_t>();
        assert(MOLECULE_FIELD_Y_LEN >= 1);
        MOLECULE_FIELD_Z_LEN = moleculeNode["field_z_len"].as<int32_t>();
        assert(MOLECULE_FIELD_Z_LEN >= 1);
        MOLECULE_DELTA_TIME = moleculeNode["delta_time"].as<double>();
        assert(MOLECULE_DELTA_TIME > 0.0);

        switch (ALGORITHM_TYPE) {
            case AlgorithmType::Naive:
            {
                break;
            }
            case AlgorithmType::CellList:
            {
                auto&& cellListNode = config["cell_list"];
                CELL_LIST_GRID_SIZE_MAGNIFICATION = cellListNode["grid_size_mag"].as<int32_t>();
                int32_t tmp             = CELL_LIST_GRID_SIZE_MAGNIFICATION;
                while (tmp > 1) {
                    assert(tmp % 2 == 0);
                    tmp >>= 1;
                }
                CELL_LIST_SEARCH_RADIUS = cellListNode["search_radius"].as<int32_t>();
                assert(CELL_LIST_SEARCH_RADIUS >= 0);
                break;
            }

            case AlgorithmType::BarnesHut:
            {
                break;
            }
            case AlgorithmType::Cluster:
            {
                auto&& clusterNode = config["cluster"];
                CLUSTER_LAMBDA = clusterNode["lambda"].as<double>();
                CLUSTER_REVERSE_LAMBDA = 1.0 / CLUSTER_LAMBDA;
                break;
            }
                
        }
        

    } catch (YAML::ParserException& e) {
        std::cerr << e.what() << std::endl;

        return false;
    }
    catch (YAML::BadFile& e) {
        std::cerr << e.what() << std::endl;

        return false;
    }

    return true;
}

void SimulationSettings::printSettings()
{
    std::cout << "ALGORITHM TYPE : ";
    switch (ALGORITHM_TYPE) {
        case AlgorithmType::Naive:     ::std::cout << "NAIVE";      break;
        case AlgorithmType::CellList:  ::std::cout << "CELL-LIST";  break;
        case AlgorithmType::BarnesHut: ::std::cout << "BARNES-HUT"; break;
        case AlgorithmType::Cluster:   ::std::cout << "CLUSTER";    break;
    }
    ::std::cout << ::std::endl;

    std::cout << "CELL SEED : " << CELL_SEED << std::endl;
    std::cout << "SIM STEP : " << SIM_STEP << std::endl;
    std::cout << "OUTPUT INTERVAL STEP : " << OUTPUT_INTERVAL_STEP << std::endl;
    std::cout << "CELL NUM : " << CELL_NUM << std::endl;
    std::cout << "POSITION UPDATE METHOD : " << NAMEOF_ENUM(POSITION_UPDATE_METHOD) << std::endl;
    std::cout << "CELL-LIST GRID SIZE MAGNIFICATION : " << CELL_LIST_GRID_SIZE_MAGNIFICATION << std::endl;
    std::cout << "CELL-LIST SEARCH RADIUS : " << CELL_LIST_SEARCH_RADIUS << std::endl;
    std::cout << "FIELD X LEN : " << FIELD_X_LEN << std::endl;
    std::cout << "FIELD Y LEN : " << FIELD_Y_LEN << std::endl;
    std::cout << "FIELD Z LEN : " << FIELD_Z_LEN << std::endl;
    std::cout << "MOLECULE TYPE NUM : " << MOLECULE_TYPE_NUM << std::endl;
    std::cout << "DEFAULT MOLECULE NUMS : ";
    for (auto& num : DEFAULT_MOLECULE_NUMS) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "MOLECULE FIELD X LEN : " << MOLECULE_FIELD_X_LEN << std::endl;
    std::cout << "MOLECULE FIELD Y LEN : " << MOLECULE_FIELD_Y_LEN << std::endl;
    std::cout << "MOLECULE FIELD Z LEN : " << MOLECULE_FIELD_Z_LEN << std::endl;
    std::cout << "DELTA TIME : " << DELTA_TIME << std::endl;
    std::cout << "MOLECULE DELTA TIME : " << MOLECULE_DELTA_TIME << std::endl;
}

// staticメンバの初期化
constinit AlgorithmType SimulationSettings::ALGORITHM_TYPE                = AlgorithmType::Naive;
constinit int32_t SimulationSettings::CELL_SEED                           = 0;
constinit int32_t SimulationSettings::SIM_STEP                            = 0;
constinit int32_t SimulationSettings::OUTPUT_INTERVAL_STEP                = 0;
constinit int32_t SimulationSettings::CELL_NUM                            = 0;
constinit PositionUpdateMethod SimulationSettings::POSITION_UPDATE_METHOD = PositionUpdateMethod::AB4;
constinit int32_t SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION   = 0;
constinit int32_t SimulationSettings::CELL_LIST_SEARCH_RADIUS             = 0;
constinit double SimulationSettings::CLUSTER_LAMBDA                       = 0;
constinit double SimulationSettings::CLUSTER_REVERSE_LAMBDA               = 0;
constinit int32_t SimulationSettings::FIELD_X_LEN                         = 0;
constinit int32_t SimulationSettings::FIELD_Y_LEN                         = 0;
constinit int32_t SimulationSettings::FIELD_Z_LEN                         = 0;
std::vector<int64_t> SimulationSettings::DEFAULT_MOLECULE_NUMS            = {};
constinit int32_t SimulationSettings::MOLECULE_TYPE_NUM                   = 0;
constinit int32_t SimulationSettings::MOLECULE_FIELD_X_LEN                = 0;
constinit int32_t SimulationSettings::MOLECULE_FIELD_Y_LEN                = 0;
constinit int32_t SimulationSettings::MOLECULE_FIELD_Z_LEN                = 0;
constinit double SimulationSettings::DELTA_TIME                           = 0.0;
constinit double SimulationSettings::MOLECULE_DELTA_TIME                  = 0.0;
