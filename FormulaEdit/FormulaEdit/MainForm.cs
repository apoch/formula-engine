using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace FormulaEdit
{
    public partial class MainForm : Form
    {
        MudData CurrentLoadedData = null;



        private class RoomConnection
        {
            public string Direction = "";
            public string Endpoint = "";

            public override string ToString()
            {
                return Direction + " -> " + Endpoint;
            }
        }


        public MainForm()
        {
            InitializeComponent();


            UserEventActionsPanel.Resize += (ctl, args) =>
            {
                Utilities.ResizeControls(UserEventActionsPanel);
            };

            RoomEventLayoutPanel.Resize += (ctl, args) =>
            {
                Utilities.ResizeControls(RoomEventLayoutPanel);
            };


            FolderPicker.SelectedPath = Properties.Settings.Default.LastWorkingPath;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (FolderPicker.ShowDialog() == DialogResult.OK)
            {
                Properties.Settings.Default.LastWorkingPath = FolderPicker.SelectedPath;
                Properties.Settings.Default.Save();

                CurrentLoadedData = MudData.LoadFromFolder(FolderPicker.SelectedPath);
                RefreshControls();
            }
        }

        private void RefreshControls()
        {
            RefreshCommandsTab();
            RefreshRoomsTab();
            RefreshItemsTab();
            RefreshTextTab();
            RefreshUserTab();
        }

        private void RefreshCommandsTab()
        {
            CommandListBox.Items.Clear();

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Commands == null)
                return;

            foreach (MudData.Command cmd in CurrentLoadedData.Commands)
            {
                CommandListBox.Items.Add(cmd);
            }

            CommandListBox_SelectedIndexChanged(null, null);
        }

        private void RefreshRoomsTab()
        {
            RoomListBox.Items.Clear();

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Rooms == null)
                return;

            foreach (MudData.Room room in CurrentLoadedData.Rooms)
            {
                RoomListBox.Items.Add(room);
            }

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RefreshUserTab()
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name != "User")
                    continue;

                RefreshUserBindingsTab(archetype);
                RefreshUserListsTab(archetype);
                RefreshUserPropertiesTab(archetype);
                RefreshUserEventsTab(archetype);

                break;
            }
        }

        private void RefreshItemsTab()
        {
            ItemsListBox.Items.Clear();
            ItemNameTextBox.Text = "";
            ItemTextTokenTextBox.Text = "";

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            foreach (var scriptable in CurrentLoadedData.Scriptables)
            {
                if (scriptable.name.StartsWith("ITEM_"))
                {
                    ItemsListBox.Items.Add(scriptable);
                }
            }
        }


        private void RefreshUserBindingsTab(MudData.Archetype userArchetype)
        {
            UserBindingsTextBox.Text = string.Join("\r\n", userArchetype.bindings);
        }

        private void RefreshUserListsTab(MudData.Archetype userArchetype)
        {
            UserListsListBox.Items.Clear();

            foreach (var list in userArchetype.lists)
            {
                UserListsListBox.Items.Add(list);
            }
        }

        private void RefreshUserPropertiesTab(MudData.Archetype userArchetype)
        {
            UserPropertiesListBox.Items.Clear();

            if (userArchetype.properties == null)
                return;

            foreach (var prop in userArchetype.properties)
            {
                UserPropertiesListBox.Items.Add(prop.Key);
            }
        }

        private void RefreshUserEventsTab(MudData.Archetype userArchetype)
        {
            UserEventsListBox.Items.Clear();

            if (userArchetype.events == null)
                return;

            foreach (var e in userArchetype.events)
            {
                UserEventsListBox.Items.Add(e);
            }
        }

        private void CommandListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
            {
                CommandName.Text = "";
                CommandEventName.Text = "";
                CommandHelpTextBox.Text = "";

                return;
            }

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            CommandName.Text = cmd.command;
            CommandEventName.Text = cmd.@event;
            CommandHelpTextBox.Text = cmd.helpText;
        }

        private void CommandApplyButton_Click(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
                return;

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            cmd.command = CommandName.Text;
            cmd.@event = CommandEventName.Text;
            cmd.helpText = CommandHelpTextBox.Text;

            RefreshCommandsTab();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (FolderPicker.ShowDialog() != DialogResult.OK)
                return;

            Properties.Settings.Default.LastWorkingPath = FolderPicker.SelectedPath;
            Properties.Settings.Default.Save();

            CurrentLoadedData.SaveToFolder(FolderPicker.SelectedPath);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void AddCommandButton_Click(object sender, EventArgs e)
        {
            var cmd = new MudData.Command();
            cmd.command = "unnamed";
            cmd.@event = "CMD_unnamed";
            cmd.helpText = "Unspecified";

            CurrentLoadedData.Commands.Add(cmd);
            RefreshCommandsTab();
        }

        private void RemoveCommandButton_Click(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
                return;

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            CurrentLoadedData.Commands.Remove(cmd);
            RefreshCommandsTab();
        }

        private void RoomListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RoomConnectionsListBox.Items.Clear();
            RoomConnectionEndpointListBox.Items.Clear();
            RoomListsListBox.Items.Clear();
            RoomEventListBox.Items.Clear();

            if (RoomListBox.SelectedItem == null)
            {
                RoomInternalName.Text = "";
                RoomDescription.Text = "";
            }
            else
            {
                var room = RoomListBox.SelectedItem as MudData.Room;

                RoomInternalName.Text = room.name;
                RoomDescription.Text = room.description;

                foreach (var conn in room.connections)
                {
                    var connWrap = new RoomConnection();
                    connWrap.Direction = conn.Key;
                    connWrap.Endpoint = conn.Value;

                    RoomConnectionsListBox.Items.Add(connWrap);
                }

                RoomConnectionsListBox_SelectedIndexChanged(null, null);

                if (room.lists != null)
                {
                    foreach (var list in room.lists)
                    {
                        RoomListsListBox.Items.Add(list);
                    }
                }

                RoomListsListBox_SelectedIndexChanged(null, null);

                if (room.events != null)
                {
                    foreach (var item in room.events)
                    {
                        RoomEventListBox.Items.Add(item);
                    }
                }

                RoomEventListBox_SelectedIndexChanged(null, null);
            }
        }

        private void RoomConnectionsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RoomConnectionEndpointListBox.Items.Clear();

            if (RoomConnectionsListBox.SelectedItem == null)
            {
                RoomConnectionDirection.Text = "";
            }
            else
            {
                var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;

                RoomConnectionDirection.Text = conn.Direction;

                var room = RoomListBox.SelectedItem as MudData.Room;

                foreach (MudData.Room r in RoomListBox.Items)
                {
                    if (r == room)
                        continue;

                    RoomConnectionEndpointListBox.Items.Add(r);

                    if (r.name == conn.Endpoint)
                        RoomConnectionEndpointListBox.SelectedItem = r;
                }
            }
        }

        private void RoomListsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (RoomListsListBox.SelectedItem == null)
            {
                RoomListName.Text = "";
                RoomListContents.Text = "";
            }
            else
            {
                var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

                RoomListName.Text = list.name;
                RoomListContents.Text = (list.contents != null) ? string.Join("\r\n", list.contents) : "";
            }
        }

        private void RoomEventListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RoomEventLayoutPanel.Controls.Clear();

            if (RoomEventListBox.SelectedItem == null)
            {
                RoomEventCode.Text = "";
            }
            else
            {
                var theEvent = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

                RoomEventCode.Text = theEvent.name;

                ScriptActionEditControl.PopulatePanel(theEvent.actions, RoomEventLayoutPanel);
            }
        }

        private void RoomConnectionAddButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            room.connections.Add("unnamed", "unspecified");

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomConnectionRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomConnectionsListBox.SelectedItem == null)
                return;

            var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;
            var room = RoomListBox.SelectedItem as MudData.Room;

            room.connections.Remove(conn.Direction);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomConnectionApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomConnectionsListBox.SelectedItem == null)
                return;

            if (RoomConnectionEndpointListBox.SelectedItem == null)
                return;

            var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;
            var room = RoomListBox.SelectedItem as MudData.Room;

            room.connections.Remove(conn.Direction);

            conn.Direction = RoomConnectionDirection.Text;
            conn.Endpoint = (RoomConnectionEndpointListBox.SelectedItem as MudData.Room).name;

            room.connections.Add(conn.Direction, conn.Endpoint);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomAddButton_Click(object sender, EventArgs e)
        {
            var room = new MudData.Room();
            room.name = "Unnamed";

            CurrentLoadedData.Rooms.Add(room);

            RefreshRoomsTab();
        }

        private void RoomRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            CurrentLoadedData.Rooms.Remove(room);

            RefreshRoomsTab();
        }

        private void RoomApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            room.name = RoomInternalName.Text;
            room.description = RoomDescription.Text;

            RefreshRoomsTab();
        }

        private void RoomListAddButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;

            var newlist = new MudData.FormulaList();
            newlist.name = "unnamed";

            room.lists.Add(newlist);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomListRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomListsListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

            room.lists.Remove(list);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomListApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomListsListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

            list.name = RoomListName.Text;

            list.contents = new List<string>(RoomListContents.Text.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries));

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomEventAddButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;

            var item = new MudData.FormulaEvent();
            item.name = "unnamed";

            room.events.Add(item);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomEventRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var room = RoomListBox.SelectedItem as MudData.Room;
            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

            room.events.Remove(item);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomEventApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

            item.name = RoomEventCode.Text;
            item.actions = ScriptActionEditControl.PopulateMudData(RoomEventLayoutPanel.Controls);

            RoomListBox_SelectedIndexChanged(null, null);
        }

        private void RoomEventNewActionButton_Click(object sender, EventArgs e)
        {
            RoomEventLayoutPanel.Controls.Clear();

            if (RoomListBox.SelectedItem == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;
            item.actions.Add(new MudData.FormulaAction());

            ScriptActionEditControl.PopulatePanel(item.actions, RoomEventLayoutPanel);
        }

        private void UserEventsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            UserEventActionsPanel.Controls.Clear();

            if (UserEventsListBox.SelectedItem == null)
            {
                UserEventsEventCodeTextBox.Text = "";
                return;
            }

            var item = UserEventsListBox.SelectedItem as MudData.FormulaEvent;

            UserEventsEventCodeTextBox.Text = item.name;
            ScriptActionEditControl.PopulatePanel(item.actions, UserEventActionsPanel);
        }

        private void UserPropertiesAddPropertyButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.properties.Add("unnamed", "0");

                    RefreshUserPropertiesTab(archetype);
                    break;
                }
            }
        }

        private void UserEventsApplyButton_Click(object sender, EventArgs e)
        {
            if (UserEventsListBox.SelectedItem == null)
                return;

            var item = UserEventsListBox.SelectedItem as MudData.FormulaEvent;

            item.name = UserEventsEventCodeTextBox.Text;
            item.actions = ScriptActionEditControl.PopulateMudData(UserEventActionsPanel.Controls);

            UserEventsListBox_SelectedIndexChanged(null, null);
        }

        private void UserListsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (UserListsListBox.SelectedItem == null)
                return;

            var list = UserListsListBox.SelectedItem as MudData.FormulaList;

            UserListsListNameTextBox.Text = list.name;
            UserListsListContentsTextBox.Text = string.Join("\r\n", list.contents);
        }

        private void AddItemButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            var scriptable = new MudData.Scriptable();
            scriptable.name = "ITEM_unnamed";
            scriptable.properties["Title"] = "TEXT:UNNAMED";

            CurrentLoadedData.Scriptables.Add(scriptable);

            RefreshItemsTab();
        }

        private void RemoveItemButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            if (ItemsListBox.SelectedItem == null)
                return;

            CurrentLoadedData.Scriptables.Remove(ItemsListBox.SelectedItem as MudData.Scriptable);

            RefreshItemsTab();
        }

        private void ItemApplyChangesButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            if (ItemsListBox.SelectedItem == null)
                return;

            CurrentLoadedData.Scriptables.Remove(ItemsListBox.SelectedItem as MudData.Scriptable);

            var scriptable = new MudData.Scriptable();
            scriptable.name = ItemNameTextBox.Text;
            scriptable.properties["Title"] = ItemTextTokenTextBox.Text;

            CurrentLoadedData.Scriptables.Add(scriptable);

            RefreshItemsTab();
        }

        private void AddTextButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.TextBags == null)
                return;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    bag.textlines.Add("UNNAMED", "Enter text here");
                    RefreshTextTab();
                    break;
                }
            }
        }

        private void RemoveTextButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.TextBags == null)
                return;

            if (TextListBox.SelectedItem == null)
                return;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    bag.textlines.Remove(TextListBox.SelectedItem.ToString());
                    RefreshTextTab();
                    break;
                }
            }
        }

        private void TextApplyButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.TextBags == null)
                return;

            if (TextListBox.SelectedItem == null)
                return;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    bag.textlines.Remove(TextListBox.SelectedItem.ToString());
                    bag.textlines.Add(TextTokenTextBox.Text, TextDataBox.Text);
                    RefreshTextTab();
                    break;
                }
            }
        }

        private void UserEventsNewActionButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserEventsListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    var formulaEvent = UserEventsListBox.SelectedItem as MudData.FormulaEvent;
                    formulaEvent.actions.Add(new MudData.FormulaActionSetGoalState());

                    UserEventsListBox_SelectedIndexChanged(null, null);
                    break;
                }
            }
        }

        private void UserEventsAddEventButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserEventsListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    var formulaEvent = new MudData.FormulaEvent();
                    formulaEvent.name = "unnamed";

                    archetype.events.Add(formulaEvent);

                    RefreshUserEventsTab(archetype);
                    break;
                }
            }
        }

        private void UserEventsRemoveEventButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserEventsListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.events.Remove(UserEventsListBox.SelectedItem as MudData.FormulaEvent);

                    RefreshUserEventsTab(archetype);
                    break;
                }
            }
        }

        private void UserPropertiesRemovePropertyButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserPropertiesListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.properties.Remove(UserPropertiesListBox.SelectedItem.ToString());
                    RefreshUserPropertiesTab(archetype);
                    break;
                }
            }
        }

        private void UserPropertiesApplyButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserPropertiesListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.properties.Remove(UserPropertiesListBox.SelectedItem.ToString());
                    archetype.properties.Add(UserPropertiesPropertyNameTextBox.Text, UserPropertiesPropertyFormulaTextBox.Text);
                    RefreshUserPropertiesTab(archetype);
                    break;
                }
            }
        }

        private void UserListsAddListButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    var list = new MudData.FormulaList();
                    list.name = "unnamed";

                    archetype.lists.Add(list);

                    RefreshUserListsTab(archetype);
                    break;
                }
            }
        }

        private void UserListsRemoveListButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserListsListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.lists.Remove(UserListsListBox.SelectedItem as MudData.FormulaList);

                    RefreshUserListsTab(archetype);
                    break;
                }
            }
        }

        private void UserListsApplyChangesButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            if (UserListsListBox.SelectedItem == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.lists.Remove(UserListsListBox.SelectedItem as MudData.FormulaList);

                    var newList = new MudData.FormulaList();
                    newList.name = UserListsListNameTextBox.Text;
                    newList.contents = new List<string>(UserListsListContentsTextBox.Lines);

                    archetype.lists.Add(newList);

                    RefreshUserListsTab(archetype);
                    break;
                }
            }
        }

        private void UserBindingsApplyButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.bindings = new List<string>(UserBindingsTextBox.Lines);

                    break;
                }
            }
        }


        private void RefreshTextTab()
        {
            TextListBox.Items.Clear();
            TextTokenTextBox.Text = "";
            TextDataBox.Text = "";

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.TextBags == null)
                return;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    foreach (var line in bag.textlines)
                        TextListBox.Items.Add(line.Key);

                    break;
                }
            }
        }

        private void TextListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (TextListBox.SelectedItem == null)
            {
                TextTokenTextBox.Text = "";
                TextDataBox.Text = "";
                return;
            }

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.TextBags == null)
                return;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    TextTokenTextBox.Text = TextListBox.SelectedItem.ToString();
                    TextDataBox.Text = bag.textlines[TextTokenTextBox.Text];

                    break;
                }
            }
        }

        private void ItemsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            if (ItemsListBox.SelectedItem == null)
            {
                ItemNameTextBox.Text = "";
                ItemTextTokenTextBox.Text = "";

                return;
            }

            var scriptable = ItemsListBox.SelectedItem as MudData.Scriptable;
            ItemNameTextBox.Text = scriptable.name;
            ItemTextTokenTextBox.Text = scriptable.properties["Title"];
        }
    }
}
