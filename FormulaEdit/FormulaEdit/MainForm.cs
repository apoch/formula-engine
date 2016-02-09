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


            ItemPropertiesDataGrid.CellEndEdit += (ctl, args) =>
            {
                HighlightCommitButton(ItemApplyChangesButton);
            };


            RoomTree.AfterSelect += RoomTree_SelectedNodeChanged;

            RoomTree.ItemDrag += (ctl, args) =>
            {
                if ((args.Item as TreeNode).Tag == null)
                    return;

                RoomTree.DoDragDrop(args.Item, DragDropEffects.Move);
            };

            RoomTree.BeforeLabelEdit += (ctl, args) =>
            {
                if (args.Node.Tag != null)
                    args.CancelEdit = true;

                if (args.Node.Parent == null)
                    args.CancelEdit = true;
            };

            RoomTree.AfterLabelEdit += (ctl, args) =>
            {
                if (CurrentLoadedData == null)
                    return;

                args.Node.Text = args.Label;

                CurrentLoadedData.Folders = new List<string>();
                StashFolderNames(RoomTree.Nodes[0].Nodes, "");
            };

            RoomTree.DragEnter += (ctl, args) =>
            {
                args.Effect = DragDropEffects.Move;
            };

            RoomTree.DragDrop += (ctl, args) =>
            {
                System.Drawing.Point pt = RoomTree.PointToClient(new System.Drawing.Point(args.X, args.Y));

                var node = RoomTree.GetNodeAt(pt);
                if (node == null)
                    return;

                while (node.Tag != null)
                    node = node.Parent;

                var draggedNode = args.Data.GetData(typeof(TreeNode)) as TreeNode;
                draggedNode.Parent.Nodes.Remove(draggedNode);

                node.Nodes.Add(draggedNode);

                StashRoomFolders(RoomTree.Nodes[0].Nodes, "");
            };


            FolderPicker.SelectedPath = Properties.Settings.Default.LastWorkingPath;
            saveOnCommitToolStripMenuItem.Checked = Properties.Settings.Default.SaveOnCommit;

            RefreshControls();
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
            RoomTree.Nodes.Clear();
            var rootnode = RoomTree.Nodes.Add("Root");
            rootnode.Tag = null;

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Rooms == null)
                return;

            if (CurrentLoadedData.Folders == null)
                CurrentLoadedData.Folders = new List<string>();

            foreach (string folderPath in CurrentLoadedData.Folders)
            {
                string[] pathElements = folderPath.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
                var parentNode = rootnode;
                for (int i = 0; i < pathElements.Length; ++i)
                {
                    var matches = parentNode.Nodes.Find(pathElements[i], false);
                    if (matches.Length == 0)
                    {
                        parentNode = parentNode.Nodes.Add(pathElements[i], pathElements[i]);
                    }
                    else
                    {
                        parentNode = matches[0];
                    }
                }
            }

            foreach (MudData.Room room in CurrentLoadedData.Rooms)
            {
                if (room.editorPath == null || room.editorPath == "")
                {
                    rootnode.Nodes.Add(room.ToString(), room.ToString()).Tag = room;
                }
                else
                {
                    string[] pathElements = room.editorPath.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
                    var targetParent = rootnode;

                    for (int i = 0; i < pathElements.Length; ++i)
                    {
                        var matches = targetParent.Nodes.Find(pathElements[i], false);
                        if (matches.Length == 0)
                        {
                            targetParent = targetParent.Nodes.Add(pathElements[i], pathElements[i]);
                        }
                        else
                        {
                            targetParent = matches[0];
                        }
                    }

                    targetParent.Nodes.Add(room.ToString(), room.ToString()).Tag = room;
                }
            }

            RoomTree.ExpandAll();
            RoomTree_SelectedNodeChanged(null, null);

            StashRoomFolders(RoomTree.Nodes[0].Nodes, "");
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
            UnhighlightCommitButton(UserBindingsApplyButton);
        }

        private void RefreshUserListsTab(MudData.Archetype userArchetype)
        {
            UserListsListBox.Items.Clear();

            foreach (var list in userArchetype.lists)
            {
                UserListsListBox.Items.Add(list);
            }

            UserListsListBox_SelectedIndexChanged(null, null);
        }

        private void RefreshUserPropertiesTab(MudData.Archetype userArchetype)
        {
            UserPropertiesListBox.Items.Clear();

            if (userArchetype.properties == null)
            {
                SetEnabledControlsUserPropertiesTab(false);
                return;
            }

            foreach (var prop in userArchetype.properties)
            {
                UserPropertiesListBox.Items.Add(prop.Key);
            }

            UserPropertiesListBox_SelectedIndexChanged(null, null);
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

            UserEventsListBox_SelectedIndexChanged(null, null);
        }

        private void CommandListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
            {
                CommandName.Text = "";
                CommandEventName.Text = "";
                CommandHelpTextBox.Text = "";
                CommandParamTokens.Text = "";

                UnhighlightCommitButton(CommandApplyButton);
                SetEnabledControlsCommandsTab(false);
                return;
            }

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            CommandName.Text = cmd.command;
            CommandEventName.Text = cmd.@event;
            CommandHelpTextBox.Text = cmd.helpText;

            if (cmd.@params == null)
                CommandParamTokens.Text = "";
            else
                CommandParamTokens.Text = string.Join("\r\n", cmd.@params.ToArray());

            UnhighlightCommitButton(CommandApplyButton);
            SetEnabledControlsCommandsTab(true);
        }

        private void CommandApplyButton_Click(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
                return;

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            cmd.command = CommandName.Text;
            cmd.@event = CommandEventName.Text;
            cmd.helpText = CommandHelpTextBox.Text;
            cmd.@params = CommandParamTokens.Lines.Length > 0 ? new List<string>(CommandParamTokens.Lines) : null;

            RefreshCommandsTab();
            UnhighlightCommitButton(CommandApplyButton);
            AutoSave();

            CommandListBox.SelectedItem = cmd;
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

        private void AutoSave()
        {
            if (Properties.Settings.Default.LastWorkingPath == null)
                return;

            if (Properties.Settings.Default.LastWorkingPath.Length == 0)
                return;

            if (!saveOnCommitToolStripMenuItem.Checked)
                return;

            CurrentLoadedData.SaveToFolder(Properties.Settings.Default.LastWorkingPath);
        }
  

        private void AddCommandButton_Click(object sender, EventArgs e)
        {
            var cmd = new MudData.Command();
            cmd.command = "unnamed";
            cmd.@event = "CMD_unnamed";
            cmd.helpText = "Unspecified";

            CurrentLoadedData.Commands.Add(cmd);
            RefreshCommandsTab();

            CommandListBox.SelectedItem = cmd;
            CommandName.Focus();
            CommandName.SelectAll();
        }

        private void RemoveCommandButton_Click(object sender, EventArgs e)
        {
            if (CommandListBox.SelectedItem == null)
                return;

            var cmd = CommandListBox.SelectedItem as MudData.Command;
            CurrentLoadedData.Commands.Remove(cmd);
            RefreshCommandsTab();
        }

        private void RoomTree_SelectedNodeChanged(object sender, EventArgs e)
        {
            RoomConnectionsListBox.Items.Clear();
            RoomConnectionEndpointListBox.Items.Clear();
            RoomListsListBox.Items.Clear();
            RoomEventListBox.Items.Clear();

            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
            {
                RoomInternalName.Text = "";
                RoomDescription.Text = "";
                SetEnabledControlsRoomsTab(false);
            }
            else
            {
                var room = RoomTree.SelectedNode.Tag as MudData.Room;
                
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

                SetEnabledControlsRoomsTab(true);
            }

            UnhighlightCommitButton(RoomApplyButton);
        }

        private void RoomConnectionsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RoomConnectionEndpointListBox.Items.Clear();

            if (RoomConnectionsListBox.SelectedItem == null)
            {
                RoomConnectionDirection.Text = "";
                SetEnabledControlsRoomConnectionsTab(false);
            }
            else
            {
                var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;

                RoomConnectionDirection.Text = conn.Direction;

                var room = RoomTree.SelectedNode.Tag as MudData.Room;

                foreach (MudData.Room r in CurrentLoadedData.Rooms)
                {
                    if (r == room)
                        continue;

                    RoomConnectionEndpointListBox.Items.Add(r);

                    if (r.name == conn.Endpoint)
                        RoomConnectionEndpointListBox.SelectedItem = r;
                }

                SetEnabledControlsRoomConnectionsTab(true);
            }

            UnhighlightCommitButton(RoomConnectionApplyButton);
        }

        private void RoomListsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (RoomListsListBox.SelectedItem == null)
            {
                RoomListName.Text = "";
                RoomListContents.Text = "";

                SetEnabledControlsRoomListsTab(false);
            }
            else
            {
                var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

                RoomListName.Text = list.name;
                RoomListContents.Text = (list.contents != null) ? string.Join("\r\n", list.contents) : "";

                SetEnabledControlsRoomListsTab(true);
            }

            UnhighlightCommitButton(RoomListApplyButton);
        }

        private void RoomEventListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RoomEventLayoutPanel.Controls.Clear();

            if (RoomEventListBox.SelectedItem == null)
            {
                RoomEventCode.Text = "";
                SetEnabledControlsRoomEventsTab(false);
            }
            else
            {
                var theEvent = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

                RoomEventCode.Text = theEvent.name;

                ScriptActionEditControl.PopulatePanel(theEvent.actions, RoomEventLayoutPanel);
                SetEnabledControlsRoomEventsTab(true);
            }

            UnhighlightCommitButton(RoomEventApplyButton);
        }

        private void RoomConnectionAddButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            room.connections.Add("unnamed", "unspecified");

            RoomTree_SelectedNodeChanged(null, null);

            foreach (RoomConnection conn in RoomConnectionsListBox.Items)
            {
                if (conn.Direction == "unnamed" && conn.Endpoint == "unspecified")
                {
                    RoomConnectionsListBox.SelectedItem = conn;
                    RoomConnectionDirection.Focus();
                    RoomConnectionDirection.SelectAll();
                    break;
                }
            }
        }

        private void RoomConnectionRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomConnectionsListBox.SelectedItem == null)
                return;

            var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;
            var room = RoomTree.SelectedNode.Tag as MudData.Room;

            room.connections.Remove(conn.Direction);

            RoomTree_SelectedNodeChanged(null, null);
        }

        private void RoomConnectionApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomConnectionsListBox.SelectedItem == null)
                return;

            if (RoomConnectionEndpointListBox.SelectedItem == null)
                return;

            var conn = RoomConnectionsListBox.SelectedItem as RoomConnection;
            var room = RoomTree.SelectedNode.Tag as MudData.Room;

            if ((conn.Direction != RoomConnectionDirection.Text) && (room.connections.ContainsKey(RoomConnectionDirection.Text)))
            {
                MessageBox.Show("A connection in that direction already exists on this room, cannot commit!", "FormulaEdit", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            room.connections.Remove(conn.Direction);

            conn.Direction = RoomConnectionDirection.Text;
            conn.Endpoint = (RoomConnectionEndpointListBox.SelectedItem as MudData.Room).name;

            room.connections.Add(conn.Direction, conn.Endpoint);

            RoomTree_SelectedNodeChanged(null, null);
            AutoSave();
            UnhighlightCommitButton(RoomConnectionApplyButton);

            foreach (RoomConnection listedConnection in RoomConnectionsListBox.Items)
            {
                if (listedConnection.Direction == conn.Direction && listedConnection.Endpoint == conn.Endpoint)
                {
                    RoomConnectionsListBox.SelectedItem = listedConnection;
                    break;
                }
            }
        }

        private void RoomAddButton_Click(object sender, EventArgs e)
        {
            var room = new MudData.Room();
            room.name = "Unnamed";
            room.description = "This is an undescribed room.";
            room.editorPath = BuildFolderString(RoomTree.SelectedNode);

            var onEnterEvent = new MudData.FormulaEvent();
            onEnterEvent.name = "OnUserEnter";

            var sendDescAction = new MudData.FormulaActionSetGoalState();
            sendDescAction.action = "SetGoalState";
            sendDescAction.binding = "User";
            sendDescAction.property = "SendRoomDescription";
            sendDescAction.value = "0";

            onEnterEvent.actions.Add(sendDescAction);
            room.events.Add(onEnterEvent);

            CurrentLoadedData.Rooms.Add(room);

            RefreshRoomsTab();

            RoomTree.SelectedNode = RoomTree.Nodes.Find(room.name, true)[0];

            RoomInternalName.Focus();
            RoomInternalName.SelectAll();
        }

        private void RoomRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            CurrentLoadedData.Rooms.Remove(room);

            RefreshRoomsTab();
        }

        private void RoomApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            room.name = RoomInternalName.Text;
            room.description = RoomDescription.Text;

            RefreshRoomsTab();
            AutoSave();
            UnhighlightCommitButton(RoomApplyButton);

            RoomTree.SelectedNode = RoomTree.Nodes.Find(room.name, true)[0];
        }

        private void RoomListAddButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;

            var newlist = new MudData.FormulaList();
            newlist.name = "unnamed";

            room.lists.Add(newlist);

            RoomTree_SelectedNodeChanged(null, null);

            RoomListsListBox.SelectedItem = newlist;
            RoomListName.Focus();
            RoomListName.SelectAll();
        }

        private void RoomListRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomListsListBox.SelectedItem == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

            room.lists.Remove(list);

            RoomTree_SelectedNodeChanged(null, null);
        }

        private void RoomListApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomListsListBox.SelectedItem == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            var list = RoomListsListBox.SelectedItem as MudData.FormulaList;

            list.name = RoomListName.Text;

            list.contents = new List<string>(RoomListContents.Text.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries));

            RoomTree_SelectedNodeChanged(null, null);
            AutoSave();
            UnhighlightCommitButton(RoomListApplyButton);

            RoomListsListBox.SelectedItem = list;
        }

        private void RoomEventAddButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;

            var item = new MudData.FormulaEvent();
            item.name = "unnamed";

            room.events.Add(item);

            RoomTree_SelectedNodeChanged(null, null);

            RoomEventListBox.SelectedItem = item;
            RoomEventCode.Focus();
            RoomEventCode.SelectAll();
        }

        private void RoomEventRemoveButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var room = RoomTree.SelectedNode.Tag as MudData.Room;
            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

            room.events.Remove(item);

            RoomTree_SelectedNodeChanged(null, null);
        }

        private void RoomEventApplyButton_Click(object sender, EventArgs e)
        {
            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;

            item.name = RoomEventCode.Text;
            item.actions = ScriptActionEditControl.PopulateMudData(RoomEventLayoutPanel.Controls);

            RoomTree_SelectedNodeChanged(null, null);
            AutoSave();
            UnhighlightCommitButton(RoomEventApplyButton);

            RoomEventListBox.SelectedItem = item;
        }

        private void RoomEventNewActionButton_Click(object sender, EventArgs e)
        {
            RoomEventLayoutPanel.Controls.Clear();

            if (RoomTree.SelectedNode == null || RoomTree.SelectedNode.Tag == null)
                return;

            if (RoomEventListBox.SelectedItem == null)
                return;

            var item = RoomEventListBox.SelectedItem as MudData.FormulaEvent;
            item.actions.Add(new MudData.FormulaActionSetGoalState());

            ScriptActionEditControl.PopulatePanel(item.actions, RoomEventLayoutPanel);
            HighlightCommitButton(RoomEventApplyButton);
        }

        private void UserEventsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            UserEventActionsPanel.Controls.Clear();

            if (UserEventsListBox.SelectedItem == null)
            {
                UserEventsEventCodeTextBox.Text = "";
                UnhighlightCommitButton(UserEventsApplyButton);
                SetEnabledControlsUserEventsTab(false);
                return;
            }

            var item = UserEventsListBox.SelectedItem as MudData.FormulaEvent;

            UserEventsEventCodeTextBox.Text = item.name;
            ScriptActionEditControl.PopulatePanel(item.actions, UserEventActionsPanel);
            UnhighlightCommitButton(UserEventsApplyButton);
            SetEnabledControlsUserEventsTab(true);
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
                    if (archetype.properties == null)
                        archetype.properties = new Dictionary<string, string>();

                    archetype.properties.Add("unnamed", "0");

                    RefreshUserPropertiesTab(archetype);

                    UserPropertiesListBox.SelectedItem = "unnamed";
                    UserPropertiesPropertyNameTextBox.Focus();
                    UserPropertiesPropertyNameTextBox.SelectAll();

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
            AutoSave();
            UnhighlightCommitButton(UserEventsApplyButton);

            UserEventsListBox.SelectedItem = item;
        }

        private void UserListsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (UserListsListBox.SelectedItem == null)
            {
                UserListsListNameTextBox.Text = "";
                UserListsListContentsTextBox.Text = "";
                UnhighlightCommitButton(UserListsApplyChangesButton);
                SetEnabledControlsUserListsTab(false);
                return;
            }

            var list = UserListsListBox.SelectedItem as MudData.FormulaList;

            UserListsListNameTextBox.Text = list.name;
            UserListsListContentsTextBox.Text = string.Join("\r\n", list.contents);

            UnhighlightCommitButton(UserListsApplyChangesButton);
            SetEnabledControlsUserListsTab(true);
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

            ItemsListBox.SelectedItem = scriptable;
            ItemNameTextBox.Focus();
            ItemNameTextBox.SelectAll();
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

            foreach (DataGridViewRow row in ItemPropertiesDataGrid.Rows)
            {
                if (row.Cells.Count != 2)
                    continue;

                string key = row.Cells[0].Value.ToString();
                string value = row.Cells[1].Value.ToString();

                scriptable.properties[key] = value;
            }


            CurrentLoadedData.Scriptables.Add(scriptable);

            RefreshItemsTab();
            AutoSave();
            UnhighlightCommitButton(ItemApplyChangesButton);

            ItemsListBox.SelectedItem = scriptable;
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

            TextListBox.SelectedItem = "UNNAMED";
            TextTokenTextBox.Focus();
            TextTokenTextBox.SelectAll();
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

            string token = TextTokenTextBox.Text;

            foreach (var bag in CurrentLoadedData.TextBags)
            {
                if (bag.name == "TEXT")
                {
                    bag.textlines.Remove(TextListBox.SelectedItem.ToString());
                    bag.textlines.Add(token, TextDataBox.Text);
                    RefreshTextTab();
                    break;
                }
            }

            AutoSave();
            UnhighlightCommitButton(TextApplyButton);

            foreach (string item in TextListBox.Items)
            {
                if (item == token)
                {
                    TextListBox.SelectedItem = item;
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

            HighlightCommitButton(UserEventsApplyButton);
        }

        private void UserEventsAddEventButton_Click(object sender, EventArgs e)
        {
            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Archetypes == null)
                return;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    var formulaEvent = new MudData.FormulaEvent();
                    formulaEvent.name = "unnamed";

                    archetype.events.Add(formulaEvent);

                    RefreshUserEventsTab(archetype);

                    UserEventsListBox.SelectedItem = formulaEvent;
                    UserEventsEventCodeTextBox.Focus();
                    UserEventsEventCodeTextBox.SelectAll();
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

            string propertyName = UserPropertiesPropertyNameTextBox.Text;

            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    archetype.properties.Remove(UserPropertiesListBox.SelectedItem.ToString());
                    archetype.properties.Add(propertyName, UserPropertiesPropertyFormulaTextBox.Text);
                    RefreshUserPropertiesTab(archetype);
                    break;
                }
            }

            AutoSave();
            UnhighlightCommitButton(UserPropertiesApplyButton);

            foreach (string item in UserPropertiesListBox.Items)
            {
                if (item == propertyName)
                {
                    UserPropertiesListBox.SelectedItem = item;
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


                    UserListsListBox.SelectedItem = list;
                    UserListsListNameTextBox.Focus();
                    UserListsListNameTextBox.SelectAll();

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
                    UserListsListBox.SelectedItem = newList;
                    break;
                }
            }

            AutoSave();
            UnhighlightCommitButton(UserListsApplyChangesButton);
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

            AutoSave();
            UnhighlightCommitButton(UserBindingsApplyButton);
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
                UnhighlightCommitButton(TextApplyButton);
                SetEnabledControlsTextTab(false);
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

            UnhighlightCommitButton(TextApplyButton);
            SetEnabledControlsTextTab(true);
        }

        private void ItemsListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ItemPropertiesDataGrid.Rows.Clear();

            if (CurrentLoadedData == null)
                return;

            if (CurrentLoadedData.Scriptables == null)
                return;

            if (ItemsListBox.SelectedItem == null)
            {
                ItemNameTextBox.Text = "";
                ItemTextTokenTextBox.Text = "";

                UnhighlightCommitButton(ItemApplyChangesButton);
                SetEnabledControlsItemsTab(false);
                return;
            }

            var scriptable = ItemsListBox.SelectedItem as MudData.Scriptable;
            ItemNameTextBox.Text = scriptable.name;
            ItemTextTokenTextBox.Text = scriptable.properties["Title"];

            foreach (var kvp in scriptable.properties)
            {
                if (kvp.Key == "Title")
                    continue;

                ItemPropertiesDataGrid.Rows.Add(new object[] { kvp.Key, kvp.Value });
            }

            UnhighlightCommitButton(ItemApplyChangesButton);
            SetEnabledControlsItemsTab(true);
        }


        private void HighlightCommitButton(Button b)
        {
            b.BackColor = System.Drawing.Color.Crimson;
        }

        private void UnhighlightCommitButton(Button b)
        {
            b.BackColor = System.Drawing.Color.Transparent;
        }


        private void CommandName_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(CommandApplyButton);
        }

        private void CommandEventName_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(CommandApplyButton);
        }

        private void CommandHelpTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(CommandApplyButton);
        }

        private void CommandParamTokens_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(CommandApplyButton);
        }

        private void saveOnCommitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveOnCommitToolStripMenuItem.Checked = !saveOnCommitToolStripMenuItem.Checked;

            Properties.Settings.Default.SaveOnCommit = saveOnCommitToolStripMenuItem.Checked;
            Properties.Settings.Default.Save();
        }

        private void RoomInternalName_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomApplyButton);
        }

        private void RoomDescription_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomApplyButton);
        }

        private void RoomConnectionDirection_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomConnectionApplyButton);
        }

        private void RoomConnectionEndpointListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomConnectionApplyButton);
        }

        private void RoomListName_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomListApplyButton);
        }

        private void RoomListContents_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomListApplyButton);
        }

        private void RoomEventCode_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(RoomEventApplyButton);
        }

        private void ItemNameTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(ItemApplyChangesButton);
        }

        private void ItemTextTokenTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(ItemApplyChangesButton);
        }

        private void TextTokenTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(TextApplyButton);
        }

        private void TextDataBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(TextApplyButton);
        }

        private void UserEventsEventCodeTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserEventsApplyButton);
        }

        private void UserPropertiesListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (UserPropertiesListBox.SelectedItem == null)
            {
                UserPropertiesPropertyNameTextBox.Text = "";
                UserPropertiesPropertyFormulaTextBox.Text = "";
                UnhighlightCommitButton(UserPropertiesApplyButton);
                SetEnabledControlsUserPropertiesTab(false);
                return;
            }

            var prop = UserPropertiesListBox.SelectedItem.ToString();


            foreach (var archetype in CurrentLoadedData.Archetypes)
            {
                if (archetype.name == "User")
                {
                    UserPropertiesPropertyNameTextBox.Text = prop;
                    UserPropertiesPropertyFormulaTextBox.Text = archetype.properties[prop];

                    break;
                }
            }

            UnhighlightCommitButton(UserPropertiesApplyButton);
            SetEnabledControlsUserPropertiesTab(true);
        }

        private void UserPropertiesPropertyNameTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserPropertiesApplyButton);
        }

        private void UserPropertiesPropertyFormulaTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserPropertiesApplyButton);
        }

        private void UserListsListNameTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserListsApplyChangesButton);
        }

        private void UserListsListContentsTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserListsApplyChangesButton);
        }

        private void UserBindingsTextBox_TextChanged(object sender, EventArgs e)
        {
            HighlightCommitButton(UserBindingsApplyButton);
        }


        private void SetEnabledControlsCommandsTab(bool enabled)
        {
            CommandName.Enabled = enabled;
            CommandEventName.Enabled = enabled;
            CommandApplyButton.Enabled = enabled;

            CommandHelpTextBox.Enabled = enabled;
            CommandParamTokens.Enabled = enabled;

            RemoveCommandButton.Enabled = enabled;
        }

        private void SetEnabledControlsRoomsTab(bool enabled)
        {
            RoomInternalName.Enabled = enabled;
            RoomApplyButton.Enabled = enabled;
            RoomDescription.Enabled = enabled;
            RoomTabControls.Enabled = enabled;
            RoomRemoveButton.Enabled = enabled;
        }

        private void SetEnabledControlsRoomConnectionsTab(bool enabled)
        {
            RoomConnectionDirection.Enabled = enabled;
            RoomConnectionEndpointListBox.Enabled = enabled;
            RoomConnectionApplyButton.Enabled = enabled;
            RoomConnectionRemoveButton.Enabled = enabled;
        }

        private void SetEnabledControlsRoomListsTab(bool enabled)
        {
            RoomListName.Enabled = enabled;
            RoomListContents.Enabled = enabled;
            RoomListRemoveButton.Enabled = enabled;
            RoomListApplyButton.Enabled = enabled;
        }

        private void SetEnabledControlsRoomEventsTab(bool enabled)
        {
            RoomEventCode.Enabled = enabled;
            RoomEventNewActionButton.Enabled = enabled;
            RoomEventRemoveButton.Enabled = enabled;
            RoomEventApplyButton.Enabled = enabled;
        }

        private void SetEnabledControlsItemsTab(bool enabled)
        {
            ItemNameTextBox.Enabled = enabled;
            ItemTextTokenTextBox.Enabled = enabled;
            ItemPropertiesDataGrid.Enabled = enabled;
            ItemApplyChangesButton.Enabled = enabled;
            RemoveItemButton.Enabled = enabled;
        }

        private void SetEnabledControlsTextTab(bool enabled)
        {
            TextTokenTextBox.Enabled = enabled;
            TextApplyButton.Enabled = enabled;
            TextDataBox.Enabled = enabled;
            RemoveTextButton.Enabled = enabled;
        }

        private void SetEnabledControlsUserEventsTab(bool enabled)
        {
            UserEventsEventCodeTextBox.Enabled = enabled;
            UserEventsNewActionButton.Enabled = enabled;
            UserEventsRemoveEventButton.Enabled = enabled;
            UserEventsApplyButton.Enabled = enabled;
        }

        private void SetEnabledControlsUserListsTab(bool enabled)
        {
            UserListsListNameTextBox.Enabled = enabled;
            UserListsListContentsTextBox.Enabled = enabled;
            UserListsRemoveListButton.Enabled = enabled;
            UserListsApplyChangesButton.Enabled = enabled;
        }

        private void SetEnabledControlsUserPropertiesTab(bool enabled)
        {
            UserPropertiesPropertyNameTextBox.Enabled = enabled;
            UserPropertiesPropertyFormulaTextBox.Enabled = enabled;
            UserPropertiesRemovePropertyButton.Enabled = enabled;
            UserPropertiesApplyButton.Enabled = enabled;
        }

        private void RoomNewFolderButton_Click(object sender, EventArgs e)
        {
            TreeNode parentNode = RoomTree.SelectedNode;
            if (parentNode == null)
                parentNode = RoomTree.Nodes[0];
            else if (parentNode.Tag != null)
                parentNode = parentNode.Parent;

            parentNode.Nodes.Add("New Folder");
            StashFolderNames(RoomTree.Nodes[0].Nodes, "");
        }

        private string BuildFolderString(TreeNode node)
        {
            string ret = "";

            while (node.Parent != null)
            {
                if (node.Tag == null)
                    ret = node.Text + "/" + ret;

                node = node.Parent;
            }

            return ret;
        }

        private void StashFolderNames(TreeNodeCollection nodes, string prefix)
        {
            foreach (TreeNode node in nodes)
            {
                if (node.Tag != null)
                    continue;

                string foldername = prefix + node.Text;
                CurrentLoadedData.Folders.Add(foldername);

                StashFolderNames(node.Nodes, foldername + "/");
            }
        }

        private void StashRoomFolders(TreeNodeCollection nodes, string prefix)
        {
            foreach (TreeNode node in nodes)
            {
                if (node.Tag != null)
                {
                    var room = node.Tag as MudData.Room;
                    room.editorPath = prefix;
                }
                else
                {
                    string folderName = prefix + node.Text;
                    StashRoomFolders(node.Nodes, folderName + "/");
                }
            }
        }
    }
}