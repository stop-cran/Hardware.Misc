using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PdfConverter
{
    class CommandLineArguments
    {
        public string TopFileName { get; set; }
        public string BottomFileName { get; set; }
        public string OutptuFileName { get; set; }
        public int PageRepeatCount { get; set; }
    }
}
