using PdfSharp.Pdf;
using System;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace PdfConverter
{
    static class PdfUtils
    {
        public static PdfDocument CombineAndRepeat(PdfDocument d1, PdfDocument d2, int count)
        {
            var res = new PdfDocument();

            for (int i = 0; i < count; i++)
            {
                res.AddPage(d1.Pages[0]);
                res.AddPage(d2.Pages[0]);
            }

            return res;
        }

        public static string Recolor(string value)
        {
            return value
                .Replace("\n0 0 0 RG\n0 0 0 rg\n", "\n1 1 1 RG\n1 1 1 rg\n")
                .Replace("\n1 0 0 RG\n1 0 0 rg\n", "\n0 0 0 RG\n0 0 0 rg\n")
                .Replace("\n0 0.427 1 RG\n0 0.427 1 rg\n", "\n0 0 0 RG\n0 0 0 rg\n");
        }

        public static string Flip(string value)
        {
            double width = 0;

            return Regex.Replace(value, "((\\d+(\\.\\d+)?) )+(re|l|m|c)[^\\w]",
                m =>
                {
                    if (width == 0)
                    {
                        width = Parse(m.Groups[2].Captures[2].Value);
                        return m.Value;
                    }

                    return FlipFigure(width, m);
                });

        }

        public static void ConvertStream(PdfDocument d, Func<string, string> converter)
        {
            var contentStream = ((PdfDictionary)d.Pages[0].Elements.GetReference("/Contents").Value).Stream;

            contentStream.Value = Encoding.UTF8.GetBytes(converter(Encoding.UTF8.GetString(contentStream.Value)));
        }

        static string FlipFigure(double width, Match m)
        {
            if (m.Groups[4].Value == "re")
                return Format(width - Parse(m.Groups[2].Captures[0].Value) - Parse(m.Groups[2].Captures[2].Value)) + ' ' +
                    m.Groups[2].Captures[1].Value + ' ' +
                    m.Groups[2].Captures[2].Value + ' ' +
                    m.Groups[2].Captures[3].Value + " re\n";

            return string.Join(" ",
                m.Groups[2].Captures.Cast<Capture>()
                    .Select((c, i) => i % 2 == 0
                        ? Format(width - Parse(c.Value))
                        : c.Value))
                        + ' ' + m.Groups[4].Value + '\n';
        }

        static double Parse(string s)
        {
            return Convert.ToDouble(s, CultureInfo.InvariantCulture);
        }

        static string Format(double d)
        {
            return d.ToString("#.0000", CultureInfo.InvariantCulture);
        }
    }
}
