using System;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ImageDecode
{
    class Program
    {
        public static void Main(string[] args)
        {
            string filesource = "";
            if (args.Length == 0)
            {
                Console.Write("Input the source of the file you want to decode...\n> ");
                filesource = Console.ReadLine();
            }
            else
                filesource = args[0].Trim().Trim('\"');
            try
            {
                byte[] head =
                {
                    0x42, 0x4d, 0x36, 0x04,
                    0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x36, 0x04, 0x00, 0x00,
                    0x28, 0x00, 0x00, 0x00,
                    0x00, 0x01, 0x00, 0x00,
                    0x00, 0x01, 0x00, 0x00,
                    0x01, 0x00, 0x08, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
                };
                byte[] bts = File.ReadAllBytes(filesource);
                List<byte> lbfname = new List<byte>();
                List<byte> content = new List<byte>();
                int i = head.Length;
                while (true)
                {
                    if ((bts[i] == 0x00) && (bts[i + 1] == 0x00))
                        break;
                    lbfname.Add(bts[i]);
                    i++;
                }
                i += 2;
                while (i < bts.Length)
                {
                    content.Add(bts[i]);
                    i++;
                }
                string fname = Encoding.UTF8.GetString(lbfname.ToArray());
                File.WriteAllBytes(fname, content.ToArray());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.ToString());
            }
        }
    }
}