using Fclp;
using PdfSharp.Pdf.IO;
using System;
using System.IO;

namespace PdfConverter
{
    class Program
    {
        static bool ParseCommandLine(string[] args, out CommandLineArguments arguments, out string error)
        {
            var res = new CommandLineArguments();
            var p = new FluentCommandLineParser();

            p.Setup<string>('t')
             .Callback(arg => res.TopFileName = arg)
             .Required();

            p.Setup<string>('b')
             .Callback(arg => res.BottomFileName = arg)
             .Required();

            p.Setup<string>("out")
             .Callback(arg => res.OutptuFileName = arg)
             .Required();

            p.Setup<int>('r')
             .Callback(arg => res.PageRepeatCount = arg)
             .Required();

            var r = p.Parse(args);

            if(r.HelpCalled)
            {
                error = null;
                arguments = null;

                return false;
            }

            if (r.HasErrors)
            {
                error = r.ErrorText;
                arguments = null;

                return false;
            }

            error = null;
            arguments = res;

            return true;
        }

        [STAThread]
        static void Main(string[] args)
        {
            CommandLineArguments arguments;
            string error;

            if (ParseCommandLine(args, out arguments, out error))
                ConvertPdf(arguments);
            else
                Console.Error.WriteLine(error);
        }

        private static void ConvertPdf(CommandLineArguments arguments)
        {
            using (var inputTop = new FileStream(arguments.TopFileName, FileMode.Open, FileAccess.Read))
            using (var inputBottom = new FileStream(arguments.BottomFileName, FileMode.Open, FileAccess.Read))
            using (var result = new FileStream(arguments.OutptuFileName, FileMode.Create, FileAccess.Write))
            {
                var top = PdfReader.Open(inputTop, PdfDocumentOpenMode.Import);
                var bottom = PdfReader.Open(inputBottom, PdfDocumentOpenMode.Import);

                PdfUtils.ConvertStream(top, contentStream => PdfUtils.Flip(PdfUtils.Recolor(contentStream)));
                PdfUtils.ConvertStream(bottom, PdfUtils.Recolor);

                PdfUtils.CombineAndRepeat(top, bottom, arguments.PageRepeatCount).Save(result);
            }
        }
    }
}
