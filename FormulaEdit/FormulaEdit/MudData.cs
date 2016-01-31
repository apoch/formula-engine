using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;

namespace FormulaEdit
{
    class MudData
    {
        public static MudData LoadFromFolder(string folderName)
        {
            var ret = new MudData();
            ret.LoadCommandsFrom(folderName + "\\CommandList.json");
            ret.LoadRoomsFrom(folderName + "\\Rooms.json");
            ret.LoadMainFrom(folderName + "\\FormulaMUD.json");

            return ret;
        }

        public void SaveToFolder(string folderName)
        {
            SaveCommandsTo(folderName + "\\CommandList.json");
            SaveRoomsTo(folderName + "\\Rooms.json");
            SaveMainTo(folderName + "\\FormulaMUD.json");
        }

        [DataContract]
        public class Command
        {
            [DataMember]
            public string command = "";
            [DataMember]
            public string @event = "";
            [DataMember]
            public string helpText = "";

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


        [DataContract(Name = "actionobj")]
        public class FormulaAction : IExtensibleDataObject
        {
            [DataMember]
            public string action = "";


            public FormulaAction InternalAction = null;


            private ExtensionDataObject edo;
            ExtensionDataObject IExtensibleDataObject.ExtensionData
            {
                get { return edo; }
                set { edo = value; }
            }

            [OnDeserialized]
            internal void DeserializationComplete(StreamingContext context)
            {
                if (this.GetType() != typeof(FormulaAction))
                    return;

                var settings = new DataContractJsonSerializerSettings();
                settings.UseSimpleDictionaryFormat = true;

                var serializer = new DataContractJsonSerializer(typeof(FormulaAction), settings);
                var stream = new MemoryStream();

                serializer.WriteObject(stream, this);
                stream.Position = 0;

                if (action == "AddSelfToList")
                {
                    RoundtripSelfIntoType<FormulaActionAddSelfToList>(stream, settings);
                }
                else if (action == "CreateListMember")
                {
                    RoundtripSelfIntoType<FormulaActionCreateListMember>(stream, settings);
                }
                else if (action == "if")
                {
                    RoundtripSelfIntoType<FormulaActionIf>(stream, settings);
                }
                else if (action == "foreach")
                {
                    RoundtripSelfIntoType<FormulaActionForEach>(stream, settings);
                }
                else if (action == "ListTransfer")
                {
                    RoundtripSelfIntoType<FormulaActionListTransfer>(stream, settings);
                }
                else if (action == "RepeatEvent")
                {
                    RoundtripSelfIntoType<FormulaActionRepeatEvent>(stream, settings);
                }
                else if (action == "SetGoalState")
                {
                    RoundtripSelfIntoType<FormulaActionSetGoalState>(stream, settings);
                }
                else if (action == "SetProperty")
                {
                    RoundtripSelfIntoType<FormulaActionSetProperty>(stream, settings);
                }
                else if (action == "TriggerEvent")
                {
                    RoundtripSelfIntoType<FormulaActionTriggerEvent>(stream, settings);
                }
                else
                {
                    throw new NotImplementedException();
                }
            }

            private void RoundtripSelfIntoType<T>(Stream stream, DataContractJsonSerializerSettings settings) where T : FormulaAction
            {
                var deserializer = new DataContractJsonSerializer(typeof(T), settings);
                var inner = deserializer.ReadObject(stream) as T;

                InternalAction = inner;
            }
        }


        [DataContract]
        public class FormulaActionAddSelfToList : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string target = "";
        }

        [DataContract]
        public class FormulaActionCreateListMember : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string archetype = "";

            [DataMember]
            public Dictionary<string, string> @params = new Dictionary<string, string>();
        }

        [DataContract]
        public class FormulaActionIf : FormulaAction
        {
            [DataMember]
            public string condition = "";

            [DataMember]
            public List<FormulaAction> actions = new List<FormulaAction>();

            [DataMember]
            public List<FormulaAction> @else = new List<FormulaAction>();
        }

        [DataContract]
        public class FormulaActionForEach : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public List<FormulaAction> actions = new List<FormulaAction>();
        }

        [DataContract]
        public class FormulaActionListTransfer : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string condition = "";

            [DataMember]
            public string scriptable = "";

            [DataMember]
            public string target = "";

            [DataMember]
            public string targetList = "";
        }

        [DataContract]
        public class FormulaActionRepeatEvent : FormulaAction
        {
            [DataMember]
            public string @event = "";

            [DataMember]
            public string count = "";

            [DataMember]
            public Dictionary<string, string> @params = new Dictionary<string, string>();
        }

        [DataContract]
        public class FormulaActionSetGoalState : FormulaAction
        {
            [DataMember]
            public string binding = "";

            [DataMember]
            public string property = "";

            [DataMember]
            public string value = "";
        }

        [DataContract]
        public class FormulaActionSetProperty : FormulaAction
        {
            [DataMember]
            public string property = "";

            [DataMember]
            public string value = "";
        }

        [DataContract]
        public class FormulaActionTriggerEvent : FormulaAction
        {
            [DataMember]
            public string @event = "";

            [DataMember]
            public string target = "";

            [DataMember]
            public Dictionary<string, string> @params = new Dictionary<string, string>();
        }



        [DataContract]
        public class FormulaEvent
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public List<FormulaAction> actions = new List<FormulaAction>();

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



        [DataContract]
        public class Archetype
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public List<string> bindings = new List<string>();

            [DataMember]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember]
            public List<FormulaEvent> events = new List<FormulaEvent>();

            [DataMember]
            public Dictionary<string, string> properties = new Dictionary<string, string>();


            public override string ToString()
            {
                return name;
            }
        }

        [DataContract]
        public class Scriptable
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember]
            public List<FormulaEvent> events = new List<FormulaEvent>();

            [DataMember]
            public Dictionary<string, string> properties = new Dictionary<string, string>();


            public override string ToString()
            {
                return name;
            }
        }

        [DataContract]
        public class TextBag
        {
            [DataMember]
            public string name = "";

            [DataMember]
            public Dictionary<string, string> textlines = new Dictionary<string, string>();


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        private class MainJSONWrapper
        {
            [DataMember]
            public List<Archetype> archetypes = new List<Archetype>();

            [DataMember]
            public List<Scriptable> scriptables = new List<Scriptable>();

            [DataMember]
            public List<TextBag> textbags = new List<TextBag>();
        }


        public List<Command> Commands = null;
        public List<Room> Rooms = null;

        public List<Archetype> Archetypes = null;
        public List<Scriptable> Scriptables = null;
        public List<TextBag> TextBags = null;


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


        private void LoadMainFrom(string fileName)
        {
            var settings = new DataContractJsonSerializerSettings();
            settings.UseSimpleDictionaryFormat = true;

            var serializer = new DataContractJsonSerializer(typeof(MainJSONWrapper), settings);
            var infile = new FileStream(fileName, FileMode.Open);

            var obj = serializer.ReadObject(infile) as MainJSONWrapper;
            Archetypes = obj.archetypes;
            Scriptables = obj.scriptables;
            TextBags = obj.textbags;

            infile.Close();
            infile.Dispose();
        }

        private void SaveMainTo(string fileName)
        {
            // TODO - implement export of main JSON file
        }
    }
}
