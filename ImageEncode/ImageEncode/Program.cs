using System;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ImageEncode
{
    class Program
    {
        static void Main(string[] args)
        {
            string filesource = "";
            if (args.Length == 0)
            {
                Console.Write("Input the source of the file you want to encrypt...\n> ");
                filesource = Console.ReadLine();
            }
            else
                filesource = args[0];
            try
            {
                byte[] bts = File.ReadAllBytes(filesource);
                string[] fname = filesource.Split(new char[] { '\\', '/' });
                byte[] bfname = Encoding.UTF8.GetBytes(fname[fname.Length - 1]);
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
                List<byte> outputlist = new List<byte>();
                Console.WriteLine("Writing Head...");
                for (int i = 0; i < head.Length; i++)
                    outputlist.Add(head[i]);
                for (int j = 0; j < bfname.Length; j++)
                    outputlist.Add(bfname[j]);
                outputlist.Add(0x00);
                outputlist.Add(0x00);
                Console.WriteLine("Generating...");
                for (int k = 0; k < bts.Length; k++)
                    outputlist.Add(bts[k]);
                File.WriteAllBytes("output.bmp", outputlist.ToArray());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.ToString());
            }
        }
    }
}
