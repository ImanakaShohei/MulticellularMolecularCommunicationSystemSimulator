using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    public static class Messages
    {
        private static bool s_isInitialized = false;
        private static readonly Dictionary<string, string> s_map = new Dictionary<string, string>();

        private static string GetLanguage() => System.Globalization.CultureInfo.CurrentCulture.Name[2..];
        

        private static void LoadMessages(string folderPath, string fileName)
        {
            using StreamReader sr = new StreamReader($"{folderPath}/{fileName}");

            while (!sr.EndOfStream)
            {
                string? line = sr.ReadLine();

                if (line is null) break;
                if (line.Length == 0) continue;

                string[] pair = line.Split('=');

                if (pair.Length != 2) throw new FormatException("The format of the language file is invalid.");
            
                s_map.Add(pair[0], pair[1]);
            }
        }

        private static void LoadSingleMessage()
        {
            throw new NotImplementedException();
        }

        private static void SetMessage(string languageName)
        {
            string folderPath = $"./languages/{languageName}/";

            if (!Path.Exists(folderPath))
            {
                // 無限ループ防止
                if (languageName == "en") throw new DirectoryNotFoundException("The path './languages/en/' was not found.");

                SetMessage("en");

                return;
            }

            LoadMessages(folderPath, "general.txt");
        }

        internal static bool Initialize()
        {
            if (s_isInitialized) return false;

            SetMessage(GetLanguage());

            s_isInitialized = true;

            return true;
        }

        public static bool IsInitialized => s_isInitialized;

        /// <summary>
        /// メッセージを取得
        /// </summary>
        /// <param name="name">メッセージ名</param>
        /// <returns>メッセージ</returns>
        public static string Get(string name) => s_map[name];

        
    }
}
