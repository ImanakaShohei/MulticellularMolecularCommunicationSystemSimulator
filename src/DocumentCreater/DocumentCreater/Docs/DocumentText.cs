using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DocumentCreater.Docs
{
    public class DocumentText : DocumentObject, IDocumentText
    {

        public readonly List<IDocumentText> Texts;
        private string m_plainText;

        public string Text
        {
            get
            {
                if (Texts.Count == 0) return m_plainText;
                var builder = new StringBuilder();

                foreach (var text in Texts)
                {
                    builder.Append(text);
                }

                return builder.ToString();
            }
            set
            {
                Texts.Clear();
                m_plainText = value;
            }
        }

        public DocumentText() : this("")
        {
        }

        public DocumentText(string text)
        {
            Texts = [];
            m_plainText = text;
        }
    }
}
