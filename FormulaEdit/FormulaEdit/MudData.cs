using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;

namespace FormulaEdit
{
    class MudData
    {
        public static MudData LoadFromFolder(string folderName)
        {
            var ret = new MudData();
            ret.LoadCommandsFrom(folderName + "\\CommandList.json");

            return ret;
        }

        public void SaveToFolder(string folderName)
        {
            SaveCommandsTo(folderName + "\\CommandList.json");
        }

        [DataContract]
        public class Command
        {
            [DataMember] public string command = "";
            [DataMember] public string @event = "";
            [DataMember] public string helpText = "";

            public override string ToString()
            {
                return command;
            }
        }

        [DataContract]
        private class CommandListJSONWrapper
        {
            [DataMember]
            public List<Command> commands = null;
        }


        public List<Command> Commands = null;


        private void LoadCommandsFrom(string fileName)
        {
            var serializer = new DataContractJsonSerializer(typeof(CommandListJSONWrapper));
            var infile = new FileStream(fileName, FileMode.Open);

            var obj = serializer.ReadObject(infile) as CommandListJSONWrapper;
            Commands = obj.commands;

            infile.Close();
            infile.Dispose();
        }

        private void SaveCommandsTo(string fileName)
        {
            var serializer = new DataContractJsonSerializer(typeof(CommandListJSONWrapper));

            var outfile = new FileStream(fileName, FileMode.Create);
            var writer = JsonReaderWriterFactory.CreateJsonWriter(outfile, Encoding.UTF8, false, true, "  ");

            var wrap = new CommandListJSONWrapper();
            wrap.commands = Commands;

            serializer.WriteObject(writer, wrap);

            writer.Flush();

            outfile.Flush();
            outfile.Close();
            outfile.Dispose();
        }
    }
}
