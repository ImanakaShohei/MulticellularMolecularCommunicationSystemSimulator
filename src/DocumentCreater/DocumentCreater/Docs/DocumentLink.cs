using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DocumentCreater.Docs
{
    public class DocumentLink : DocumentObject, IDocumentText
    {
        public string Text { get; }
        public readonly string Path;
        public DocumentLink(string text, string path)
        {
            Text = text;
            Path = path;
        }
    }
}
