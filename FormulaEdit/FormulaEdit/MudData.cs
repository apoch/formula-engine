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
            ret.LoadRoomsFrom(folderName + "\\Rooms.json");

            return ret;
        }

        public void SaveToFolder(string folderName)
        {
            SaveCommandsTo(folderName + "\\CommandList.json");
            SaveRoomsTo(folderName + "\\Rooms.json");
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


        [DataContract]
        public class FormulaList
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public List<string> contents = null;


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        public class FormulaEvent
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public List<Dictionary<string, string>> actions = new List<Dictionary<string, string>>();


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        public class Room
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public string description = "";

            [DataMember]
            public Dictionary<string, string> connections = new Dictionary<string, string>();

            [DataMember]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember]
            public List<FormulaEvent> events = new List<FormulaEvent>();


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        private class RoomListJSONWrapper
        {
            [DataMember]
            public List<Room> rooms = null;
        }


        public List<Command> Commands = null;
        public List<Room> Rooms = null;


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


        private void LoadRoomsFrom(string fileName)
        {
            var settings = new DataContractJsonSerializerSettings();
            settings.UseSimpleDictionaryFormat = true;

            var serializer = new DataContractJsonSerializer(typeof(RoomListJSONWrapper), settings);
            var infile = new FileStream(fileName, FileMode.Open);

            var obj = serializer.ReadObject(infile) as RoomListJSONWrapper;
            Rooms = obj.rooms;

            infile.Close();
            infile.Dispose();
        }

        private void SaveRoomsTo(string fileName)
        {
            var settings = new DataContractJsonSerializerSettings();
            settings.UseSimpleDictionaryFormat = true;

            var serializer = new DataContractJsonSerializer(typeof(RoomListJSONWrapper), settings);

            var outfile = new FileStream(fileName, FileMode.Create);
            var writer = JsonReaderWriterFactory.CreateJsonWriter(outfile, Encoding.UTF8, false, true, "  ");

            var wrap = new RoomListJSONWrapper();
            wrap.rooms = Rooms;

            serializer.WriteObject(writer, wrap);

            writer.Flush();

            outfile.Flush();
            outfile.Close();
            outfile.Dispose();
        }
    }
}
