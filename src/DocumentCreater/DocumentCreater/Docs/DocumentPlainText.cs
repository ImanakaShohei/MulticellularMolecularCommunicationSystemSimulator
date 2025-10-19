using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DocumentCreater.Docs
{
    public class DocumentPlainText : DocumentObject, IDocumentText
    {
        public string Text { get; set; }

        public DocumentPlainText() : this("")
        {
        }

        public DocumentPlainText(string text)
        {
            Text = text;
        }
    }
}
