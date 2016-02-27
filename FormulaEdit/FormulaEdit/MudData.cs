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

        public static MudData Current = null;


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

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<string> @params = null;

            public override string ToString()
            {
                return command;
            }
        }

        [DataContract]
        private class CommandListJSONWrapper
        {
            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<Command> commands = null;
        }


        [DataContract]
        public class FormulaList
        {
            [DataMember]
            public string name = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
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

            [OnSerializing]
            internal void SerializationInProgress(StreamingContext context)
            {
                if (InternalAction == null)
                    return;

                var settings = new DataContractJsonSerializerSettings();
                settings.UseSimpleDictionaryFormat = true;

                var serializer = new DataContractJsonSerializer(InternalAction.GetType(), settings);
                var stream = new MemoryStream();

                serializer.WriteObject(stream, InternalAction);
                stream.Position = 0;

                var deserializer = new DataContractJsonSerializer(typeof(FormulaAction), settings);
                var temp = deserializer.ReadObject(stream) as FormulaAction;

                edo = temp.edo;
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

                if (action == "AddToList")
                {
                    RoundtripSelfIntoType<FormulaActionAddToList>(stream, settings);
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
                else if (action == "ListRemove")
                {
                    RoundtripSelfIntoType<FormulaActionListRemove>(stream, settings);
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
        public class FormulaActionAddToList : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string target = "";

            [DataMember]
            public string @object = "";
        }

        [DataContract]
        public class FormulaActionCreateListMember : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string archetype = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public Dictionary<string, string> @params = new Dictionary<string, string>();
        }

        [DataContract]
        public class FormulaActionIf : FormulaAction
        {
            [DataMember]
            public string condition = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaAction> actions = new List<FormulaAction>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaAction> @else = new List<FormulaAction>();
        }

        [DataContract]
        public class FormulaActionForEach : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string scriptable = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaAction> actions = new List<FormulaAction>();
        }

        [DataContract]
        public class FormulaActionListTransfer : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string condition = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string scriptable = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string target = "";

            [DataMember]
            public string targetList = "";
        }

        [DataContract]
        public class FormulaActionListRemove : FormulaAction
        {
            [DataMember]
            public string list = "";

            [DataMember]
            public string condition = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string scriptable = "";
        }

        [DataContract]
        public class FormulaActionRepeatEvent : FormulaAction
        {
            [DataMember]
            public string @event = "";

            [DataMember]
            public string count = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
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

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string target = "";
        }

        [DataContract]
        public class FormulaActionTriggerEvent : FormulaAction
        {
            [DataMember]
            public string @event = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string target = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public string delay = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public Dictionary<string, string> @params = new Dictionary<string, string>();
        }



        [DataContract]
        public class FormulaEvent
        {
            [DataMember]
            public string name = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
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
            public string editorPath = "";

            [DataMember]
            public string description = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public Dictionary<string, string> connections = new Dictionary<string, string>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaEvent> events = new List<FormulaEvent>();


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        private class RoomListJSONWrapper
        {
            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<Room> rooms = null;

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<string> folders = null;
        }



        [DataContract]
        public class Archetype
        {
            [DataMember]
            public string name = "";

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<string> bindings = new List<string>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaEvent> events = new List<FormulaEvent>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
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

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaList> lists = new List<FormulaList>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<FormulaEvent> events = new List<FormulaEvent>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
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

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public Dictionary<string, string> textlines = new Dictionary<string, string>();


            public override string ToString()
            {
                return name;
            }
        }


        [DataContract]
        private class MainJSONWrapper
        {
            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<Archetype> archetypes = new List<Archetype>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<Scriptable> scriptables = new List<Scriptable>();

            [DataMember(EmitDefaultValue = false)]
            [OptionalField]
            public List<TextBag> textbags = new List<TextBag>();
        }


        public List<Command> Commands = null;
        public List<Room> Rooms = null;
        public List<string> Folders = null;

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
            Folders = obj.folders;

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
            wrap.folders = Folders;

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
            var settings = new DataContractJsonSerializerSettings();
            settings.UseSimpleDictionaryFormat = true;
            
            var serializer = new DataContractJsonSerializer(typeof(MainJSONWrapper), settings);
            var outfile = new FileStream(fileName, FileMode.Create);

            var writer = JsonReaderWriterFactory.CreateJsonWriter(outfile, Encoding.UTF8, false, true, "  ");

            var wrap = new MainJSONWrapper();
            wrap.archetypes = Archetypes;
            wrap.scriptables = Scriptables;
            wrap.textbags = TextBags;

            serializer.WriteObject(writer, wrap);

            writer.Flush();

            outfile.Flush();
            outfile.Close();
            outfile.Dispose();
        }


        public static List<string> GenerateHintsForBindings(string archetypeName)
        {
            var ret = new List<string>();

            if (Current != null)
            {
                var archetype = Current.Archetypes.Find((a) => (a.name == archetypeName));
                if (archetype != null && archetype.bindings != null)
                {
                    ret.AddRange(archetype.bindings);
                }
            }

            if (archetypeName == "Room")
            {
                ret.Add("User");
            }

            return ret;
        }

        public static List<string> GenerateHintsForGoalStates(string bindingName)
        {
            var ret = new List<string>();

            if (Current != null)
            {
                if (bindingName == "User")
                {
                    ret.Add("EnterConnectedRoom");
                    ret.Add("EnterRoom");
                    ret.Add("SendMessage");
                    ret.Add("SendRoomDescription");
                    ret.Add("PollInput");
                }
            }

            return ret;
        }
    }
}
