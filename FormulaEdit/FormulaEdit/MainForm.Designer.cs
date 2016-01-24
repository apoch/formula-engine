namespace FormulaEdit
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MainEditorTabs = new System.Windows.Forms.TabControl();
            this.CommandsTab = new System.Windows.Forms.TabPage();
            this.CommandApplyButton = new System.Windows.Forms.Button();
            this.CommandHelpTextBox = new System.Windows.Forms.TextBox();
            this.LabelCommandHelpText = new System.Windows.Forms.Label();
            this.LabelCommandEvent = new System.Windows.Forms.Label();
            this.CommandEventName = new System.Windows.Forms.TextBox();
            this.CommandName = new System.Windows.Forms.TextBox();
            this.LabelCommandFromUser = new System.Windows.Forms.Label();
            this.RemoveCommandButton = new System.Windows.Forms.Button();
            this.AddCommandButton = new System.Windows.Forms.Button();
            this.CommandListBox = new System.Windows.Forms.ListBox();
            this.RoomsTab = new System.Windows.Forms.TabPage();
            this.RoomTabControls = new System.Windows.Forms.TabControl();
            this.RoomConnectionsTab = new System.Windows.Forms.TabPage();
            this.RoomConnectionApplyButton = new System.Windows.Forms.Button();
            this.RoomConnectionRemoveButton = new System.Windows.Forms.Button();
            this.RoomConnectionAddButton = new System.Windows.Forms.Button();
            this.RoomConnectionEndpointListBox = new System.Windows.Forms.ListBox();
            this.LabelRoomConnectionEndpoint = new System.Windows.Forms.Label();
            this.LabelRoomConnectionDirection = new System.Windows.Forms.Label();
            this.RoomConnectionDirection = new System.Windows.Forms.TextBox();
            this.RoomConnectionsListBox = new System.Windows.Forms.ListBox();
            this.RoomListsTab = new System.Windows.Forms.TabPage();
            this.RoomListApplyButton = new System.Windows.Forms.Button();
            this.RoomListRemoveButton = new System.Windows.Forms.Button();
            this.RoomListAddButton = new System.Windows.Forms.Button();
            this.RoomListContents = new System.Windows.Forms.TextBox();
            this.LabelRoomListContents = new System.Windows.Forms.Label();
            this.LabelRoomListName = new System.Windows.Forms.Label();
            this.RoomListName = new System.Windows.Forms.TextBox();
            this.RoomListsListBox = new System.Windows.Forms.ListBox();
            this.RoomEventsTab = new System.Windows.Forms.TabPage();
            this.LabelRoomEventCode = new System.Windows.Forms.Label();
            this.RoomEventCode = new System.Windows.Forms.TextBox();
            this.RoomEventListBox = new System.Windows.Forms.ListBox();
            this.RoomDescription = new System.Windows.Forms.TextBox();
            this.LabelRoomDescription = new System.Windows.Forms.Label();
            this.RoomInternalName = new System.Windows.Forms.TextBox();
            this.LabelInternalRoomName = new System.Windows.Forms.Label();
            this.RoomListBox = new System.Windows.Forms.ListBox();
            this.ItemsTab = new System.Windows.Forms.TabPage();
            this.TextTab = new System.Windows.Forms.TabPage();
            this.UserTab = new System.Windows.Forms.TabPage();
            this.PrimaryMenuStrip = new System.Windows.Forms.MenuStrip();
            this.FileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.FolderPicker = new System.Windows.Forms.FolderBrowserDialog();
            this.RoomEventLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.RoomEventNewActionButton = new System.Windows.Forms.Button();
            this.MainEditorTabs.SuspendLayout();
            this.CommandsTab.SuspendLayout();
            this.RoomsTab.SuspendLayout();
            this.RoomTabControls.SuspendLayout();
            this.RoomConnectionsTab.SuspendLayout();
            this.RoomListsTab.SuspendLayout();
            this.RoomEventsTab.SuspendLayout();
            this.PrimaryMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // MainEditorTabs
            // 
            this.MainEditorTabs.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MainEditorTabs.Controls.Add(this.CommandsTab);
            this.MainEditorTabs.Controls.Add(this.RoomsTab);
            this.MainEditorTabs.Controls.Add(this.ItemsTab);
            this.MainEditorTabs.Controls.Add(this.TextTab);
            this.MainEditorTabs.Controls.Add(this.UserTab);
            this.MainEditorTabs.Location = new System.Drawing.Point(13, 27);
            this.MainEditorTabs.Name = "MainEditorTabs";
            this.MainEditorTabs.SelectedIndex = 0;
            this.MainEditorTabs.Size = new System.Drawing.Size(737, 476);
            this.MainEditorTabs.TabIndex = 0;
            // 
            // CommandsTab
            // 
            this.CommandsTab.Controls.Add(this.CommandApplyButton);
            this.CommandsTab.Controls.Add(this.CommandHelpTextBox);
            this.CommandsTab.Controls.Add(this.LabelCommandHelpText);
            this.CommandsTab.Controls.Add(this.LabelCommandEvent);
            this.CommandsTab.Controls.Add(this.CommandEventName);
            this.CommandsTab.Controls.Add(this.CommandName);
            this.CommandsTab.Controls.Add(this.LabelCommandFromUser);
            this.CommandsTab.Controls.Add(this.RemoveCommandButton);
            this.CommandsTab.Controls.Add(this.AddCommandButton);
            this.CommandsTab.Controls.Add(this.CommandListBox);
            this.CommandsTab.Location = new System.Drawing.Point(4, 22);
            this.CommandsTab.Name = "CommandsTab";
            this.CommandsTab.Padding = new System.Windows.Forms.Padding(3);
            this.CommandsTab.Size = new System.Drawing.Size(729, 450);
            this.CommandsTab.TabIndex = 0;
            this.CommandsTab.Text = "Commands";
            this.CommandsTab.UseVisualStyleBackColor = true;
            // 
            // CommandApplyButton
            // 
            this.CommandApplyButton.Location = new System.Drawing.Point(541, 10);
            this.CommandApplyButton.Name = "CommandApplyButton";
            this.CommandApplyButton.Size = new System.Drawing.Size(113, 40);
            this.CommandApplyButton.TabIndex = 9;
            this.CommandApplyButton.Text = "Apply Changes";
            this.CommandApplyButton.UseVisualStyleBackColor = true;
            this.CommandApplyButton.Click += new System.EventHandler(this.CommandApplyButton_Click);
            // 
            // CommandHelpTextBox
            // 
            this.CommandHelpTextBox.AcceptsReturn = true;
            this.CommandHelpTextBox.Location = new System.Drawing.Point(203, 94);
            this.CommandHelpTextBox.Multiline = true;
            this.CommandHelpTextBox.Name = "CommandHelpTextBox";
            this.CommandHelpTextBox.Size = new System.Drawing.Size(520, 97);
            this.CommandHelpTextBox.TabIndex = 8;
            // 
            // LabelCommandHelpText
            // 
            this.LabelCommandHelpText.AutoSize = true;
            this.LabelCommandHelpText.Location = new System.Drawing.Point(200, 77);
            this.LabelCommandHelpText.Name = "LabelCommandHelpText";
            this.LabelCommandHelpText.Size = new System.Drawing.Size(52, 13);
            this.LabelCommandHelpText.TabIndex = 7;
            this.LabelCommandHelpText.Text = "Help text:";
            // 
            // LabelCommandEvent
            // 
            this.LabelCommandEvent.AutoSize = true;
            this.LabelCommandEvent.Location = new System.Drawing.Point(204, 37);
            this.LabelCommandEvent.Name = "LabelCommandEvent";
            this.LabelCommandEvent.Size = new System.Drawing.Size(101, 13);
            this.LabelCommandEvent.TabIndex = 6;
            this.LabelCommandEvent.Text = "Event sent to script:";
            // 
            // CommandEventName
            // 
            this.CommandEventName.Location = new System.Drawing.Point(311, 34);
            this.CommandEventName.Name = "CommandEventName";
            this.CommandEventName.Size = new System.Drawing.Size(213, 20);
            this.CommandEventName.TabIndex = 5;
            // 
            // CommandName
            // 
            this.CommandName.Location = new System.Drawing.Point(311, 7);
            this.CommandName.Name = "CommandName";
            this.CommandName.Size = new System.Drawing.Size(213, 20);
            this.CommandName.TabIndex = 4;
            // 
            // LabelCommandFromUser
            // 
            this.LabelCommandFromUser.AutoSize = true;
            this.LabelCommandFromUser.Location = new System.Drawing.Point(202, 10);
            this.LabelCommandFromUser.Name = "LabelCommandFromUser";
            this.LabelCommandFromUser.Size = new System.Drawing.Size(103, 13);
            this.LabelCommandFromUser.TabIndex = 3;
            this.LabelCommandFromUser.Text = "Command from user:";
            // 
            // RemoveCommandButton
            // 
            this.RemoveCommandButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RemoveCommandButton.Location = new System.Drawing.Point(102, 417);
            this.RemoveCommandButton.Name = "RemoveCommandButton";
            this.RemoveCommandButton.Size = new System.Drawing.Size(89, 27);
            this.RemoveCommandButton.TabIndex = 2;
            this.RemoveCommandButton.Text = "Remove";
            this.RemoveCommandButton.UseVisualStyleBackColor = true;
            this.RemoveCommandButton.Click += new System.EventHandler(this.RemoveCommandButton_Click);
            // 
            // AddCommandButton
            // 
            this.AddCommandButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.AddCommandButton.Location = new System.Drawing.Point(6, 417);
            this.AddCommandButton.Name = "AddCommandButton";
            this.AddCommandButton.Size = new System.Drawing.Size(89, 27);
            this.AddCommandButton.TabIndex = 1;
            this.AddCommandButton.Text = "Add";
            this.AddCommandButton.UseVisualStyleBackColor = true;
            this.AddCommandButton.Click += new System.EventHandler(this.AddCommandButton_Click);
            // 
            // CommandListBox
            // 
            this.CommandListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.CommandListBox.FormattingEnabled = true;
            this.CommandListBox.Location = new System.Drawing.Point(7, 7);
            this.CommandListBox.Name = "CommandListBox";
            this.CommandListBox.Size = new System.Drawing.Size(184, 381);
            this.CommandListBox.TabIndex = 0;
            this.CommandListBox.SelectedIndexChanged += new System.EventHandler(this.CommandListBox_SelectedIndexChanged);
            // 
            // RoomsTab
            // 
            this.RoomsTab.Controls.Add(this.RoomTabControls);
            this.RoomsTab.Controls.Add(this.RoomDescription);
            this.RoomsTab.Controls.Add(this.LabelRoomDescription);
            this.RoomsTab.Controls.Add(this.RoomInternalName);
            this.RoomsTab.Controls.Add(this.LabelInternalRoomName);
            this.RoomsTab.Controls.Add(this.RoomListBox);
            this.RoomsTab.Location = new System.Drawing.Point(4, 22);
            this.RoomsTab.Name = "RoomsTab";
            this.RoomsTab.Padding = new System.Windows.Forms.Padding(3);
            this.RoomsTab.Size = new System.Drawing.Size(729, 450);
            this.RoomsTab.TabIndex = 1;
            this.RoomsTab.Text = "Rooms";
            this.RoomsTab.UseVisualStyleBackColor = true;
            // 
            // RoomTabControls
            // 
            this.RoomTabControls.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RoomTabControls.Controls.Add(this.RoomConnectionsTab);
            this.RoomTabControls.Controls.Add(this.RoomListsTab);
            this.RoomTabControls.Controls.Add(this.RoomEventsTab);
            this.RoomTabControls.Location = new System.Drawing.Point(208, 171);
            this.RoomTabControls.Name = "RoomTabControls";
            this.RoomTabControls.SelectedIndex = 0;
            this.RoomTabControls.Size = new System.Drawing.Size(515, 273);
            this.RoomTabControls.TabIndex = 5;
            // 
            // RoomConnectionsTab
            // 
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionApplyButton);
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionRemoveButton);
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionAddButton);
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionEndpointListBox);
            this.RoomConnectionsTab.Controls.Add(this.LabelRoomConnectionEndpoint);
            this.RoomConnectionsTab.Controls.Add(this.LabelRoomConnectionDirection);
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionDirection);
            this.RoomConnectionsTab.Controls.Add(this.RoomConnectionsListBox);
            this.RoomConnectionsTab.Location = new System.Drawing.Point(4, 22);
            this.RoomConnectionsTab.Name = "RoomConnectionsTab";
            this.RoomConnectionsTab.Padding = new System.Windows.Forms.Padding(3);
            this.RoomConnectionsTab.Size = new System.Drawing.Size(507, 247);
            this.RoomConnectionsTab.TabIndex = 0;
            this.RoomConnectionsTab.Text = "Connections";
            this.RoomConnectionsTab.UseVisualStyleBackColor = true;
            // 
            // RoomConnectionApplyButton
            // 
            this.RoomConnectionApplyButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomConnectionApplyButton.Location = new System.Drawing.Point(381, 202);
            this.RoomConnectionApplyButton.Name = "RoomConnectionApplyButton";
            this.RoomConnectionApplyButton.Size = new System.Drawing.Size(109, 39);
            this.RoomConnectionApplyButton.TabIndex = 7;
            this.RoomConnectionApplyButton.Text = "Apply";
            this.RoomConnectionApplyButton.UseVisualStyleBackColor = true;
            // 
            // RoomConnectionRemoveButton
            // 
            this.RoomConnectionRemoveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomConnectionRemoveButton.Location = new System.Drawing.Point(266, 202);
            this.RoomConnectionRemoveButton.Name = "RoomConnectionRemoveButton";
            this.RoomConnectionRemoveButton.Size = new System.Drawing.Size(109, 39);
            this.RoomConnectionRemoveButton.TabIndex = 6;
            this.RoomConnectionRemoveButton.Text = "Remove";
            this.RoomConnectionRemoveButton.UseVisualStyleBackColor = true;
            // 
            // RoomConnectionAddButton
            // 
            this.RoomConnectionAddButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomConnectionAddButton.Location = new System.Drawing.Point(151, 202);
            this.RoomConnectionAddButton.Name = "RoomConnectionAddButton";
            this.RoomConnectionAddButton.Size = new System.Drawing.Size(109, 39);
            this.RoomConnectionAddButton.TabIndex = 5;
            this.RoomConnectionAddButton.Text = "Add";
            this.RoomConnectionAddButton.UseVisualStyleBackColor = true;
            // 
            // RoomConnectionEndpointListBox
            // 
            this.RoomConnectionEndpointListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomConnectionEndpointListBox.FormattingEnabled = true;
            this.RoomConnectionEndpointListBox.Location = new System.Drawing.Point(151, 64);
            this.RoomConnectionEndpointListBox.Name = "RoomConnectionEndpointListBox";
            this.RoomConnectionEndpointListBox.Size = new System.Drawing.Size(339, 134);
            this.RoomConnectionEndpointListBox.TabIndex = 4;
            // 
            // LabelRoomConnectionEndpoint
            // 
            this.LabelRoomConnectionEndpoint.AutoSize = true;
            this.LabelRoomConnectionEndpoint.Location = new System.Drawing.Point(148, 48);
            this.LabelRoomConnectionEndpoint.Name = "LabelRoomConnectionEndpoint";
            this.LabelRoomConnectionEndpoint.Size = new System.Drawing.Size(52, 13);
            this.LabelRoomConnectionEndpoint.TabIndex = 3;
            this.LabelRoomConnectionEndpoint.Text = "Endpoint:";
            // 
            // LabelRoomConnectionDirection
            // 
            this.LabelRoomConnectionDirection.AutoSize = true;
            this.LabelRoomConnectionDirection.Location = new System.Drawing.Point(148, 9);
            this.LabelRoomConnectionDirection.Name = "LabelRoomConnectionDirection";
            this.LabelRoomConnectionDirection.Size = new System.Drawing.Size(70, 13);
            this.LabelRoomConnectionDirection.TabIndex = 2;
            this.LabelRoomConnectionDirection.Text = "Exit direction:";
            // 
            // RoomConnectionDirection
            // 
            this.RoomConnectionDirection.Location = new System.Drawing.Point(224, 6);
            this.RoomConnectionDirection.Name = "RoomConnectionDirection";
            this.RoomConnectionDirection.Size = new System.Drawing.Size(152, 20);
            this.RoomConnectionDirection.TabIndex = 1;
            // 
            // RoomConnectionsListBox
            // 
            this.RoomConnectionsListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomConnectionsListBox.FormattingEnabled = true;
            this.RoomConnectionsListBox.Location = new System.Drawing.Point(6, 6);
            this.RoomConnectionsListBox.Name = "RoomConnectionsListBox";
            this.RoomConnectionsListBox.Size = new System.Drawing.Size(139, 238);
            this.RoomConnectionsListBox.TabIndex = 0;
            this.RoomConnectionsListBox.SelectedIndexChanged += new System.EventHandler(this.RoomConnectionsListBox_SelectedIndexChanged);
            // 
            // RoomListsTab
            // 
            this.RoomListsTab.Controls.Add(this.RoomListApplyButton);
            this.RoomListsTab.Controls.Add(this.RoomListRemoveButton);
            this.RoomListsTab.Controls.Add(this.RoomListAddButton);
            this.RoomListsTab.Controls.Add(this.RoomListContents);
            this.RoomListsTab.Controls.Add(this.LabelRoomListContents);
            this.RoomListsTab.Controls.Add(this.LabelRoomListName);
            this.RoomListsTab.Controls.Add(this.RoomListName);
            this.RoomListsTab.Controls.Add(this.RoomListsListBox);
            this.RoomListsTab.Location = new System.Drawing.Point(4, 22);
            this.RoomListsTab.Name = "RoomListsTab";
            this.RoomListsTab.Padding = new System.Windows.Forms.Padding(3);
            this.RoomListsTab.Size = new System.Drawing.Size(507, 247);
            this.RoomListsTab.TabIndex = 1;
            this.RoomListsTab.Text = "Lists";
            this.RoomListsTab.UseVisualStyleBackColor = true;
            // 
            // RoomListApplyButton
            // 
            this.RoomListApplyButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomListApplyButton.Location = new System.Drawing.Point(381, 202);
            this.RoomListApplyButton.Name = "RoomListApplyButton";
            this.RoomListApplyButton.Size = new System.Drawing.Size(109, 39);
            this.RoomListApplyButton.TabIndex = 15;
            this.RoomListApplyButton.Text = "Apply";
            this.RoomListApplyButton.UseVisualStyleBackColor = true;
            // 
            // RoomListRemoveButton
            // 
            this.RoomListRemoveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomListRemoveButton.Location = new System.Drawing.Point(266, 202);
            this.RoomListRemoveButton.Name = "RoomListRemoveButton";
            this.RoomListRemoveButton.Size = new System.Drawing.Size(109, 39);
            this.RoomListRemoveButton.TabIndex = 14;
            this.RoomListRemoveButton.Text = "Remove";
            this.RoomListRemoveButton.UseVisualStyleBackColor = true;
            // 
            // RoomListAddButton
            // 
            this.RoomListAddButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomListAddButton.Location = new System.Drawing.Point(151, 202);
            this.RoomListAddButton.Name = "RoomListAddButton";
            this.RoomListAddButton.Size = new System.Drawing.Size(109, 39);
            this.RoomListAddButton.TabIndex = 13;
            this.RoomListAddButton.Text = "Add";
            this.RoomListAddButton.UseVisualStyleBackColor = true;
            // 
            // RoomListContents
            // 
            this.RoomListContents.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RoomListContents.Location = new System.Drawing.Point(151, 64);
            this.RoomListContents.Multiline = true;
            this.RoomListContents.Name = "RoomListContents";
            this.RoomListContents.Size = new System.Drawing.Size(339, 134);
            this.RoomListContents.TabIndex = 12;
            // 
            // LabelRoomListContents
            // 
            this.LabelRoomListContents.AutoSize = true;
            this.LabelRoomListContents.Location = new System.Drawing.Point(148, 48);
            this.LabelRoomListContents.Name = "LabelRoomListContents";
            this.LabelRoomListContents.Size = new System.Drawing.Size(52, 13);
            this.LabelRoomListContents.TabIndex = 11;
            this.LabelRoomListContents.Text = "Contents:";
            // 
            // LabelRoomListName
            // 
            this.LabelRoomListName.AutoSize = true;
            this.LabelRoomListName.Location = new System.Drawing.Point(161, 9);
            this.LabelRoomListName.Name = "LabelRoomListName";
            this.LabelRoomListName.Size = new System.Drawing.Size(57, 13);
            this.LabelRoomListName.TabIndex = 10;
            this.LabelRoomListName.Text = "List Name:";
            // 
            // RoomListName
            // 
            this.RoomListName.Location = new System.Drawing.Point(224, 6);
            this.RoomListName.Name = "RoomListName";
            this.RoomListName.Size = new System.Drawing.Size(152, 20);
            this.RoomListName.TabIndex = 9;
            // 
            // RoomListsListBox
            // 
            this.RoomListsListBox.FormattingEnabled = true;
            this.RoomListsListBox.Location = new System.Drawing.Point(6, 6);
            this.RoomListsListBox.Name = "RoomListsListBox";
            this.RoomListsListBox.Size = new System.Drawing.Size(139, 238);
            this.RoomListsListBox.TabIndex = 0;
            this.RoomListsListBox.SelectedIndexChanged += new System.EventHandler(this.RoomListsListBox_SelectedIndexChanged);
            // 
            // RoomEventsTab
            // 
            this.RoomEventsTab.Controls.Add(this.RoomEventNewActionButton);
            this.RoomEventsTab.Controls.Add(this.RoomEventLayoutPanel);
            this.RoomEventsTab.Controls.Add(this.LabelRoomEventCode);
            this.RoomEventsTab.Controls.Add(this.RoomEventCode);
            this.RoomEventsTab.Controls.Add(this.RoomEventListBox);
            this.RoomEventsTab.Location = new System.Drawing.Point(4, 22);
            this.RoomEventsTab.Name = "RoomEventsTab";
            this.RoomEventsTab.Size = new System.Drawing.Size(507, 247);
            this.RoomEventsTab.TabIndex = 2;
            this.RoomEventsTab.Text = "Events";
            this.RoomEventsTab.UseVisualStyleBackColor = true;
            // 
            // LabelRoomEventCode
            // 
            this.LabelRoomEventCode.AutoSize = true;
            this.LabelRoomEventCode.Location = new System.Drawing.Point(152, 9);
            this.LabelRoomEventCode.Name = "LabelRoomEventCode";
            this.LabelRoomEventCode.Size = new System.Drawing.Size(66, 13);
            this.LabelRoomEventCode.TabIndex = 2;
            this.LabelRoomEventCode.Text = "Event Code:";
            // 
            // RoomEventCode
            // 
            this.RoomEventCode.Location = new System.Drawing.Point(224, 6);
            this.RoomEventCode.Name = "RoomEventCode";
            this.RoomEventCode.Size = new System.Drawing.Size(152, 20);
            this.RoomEventCode.TabIndex = 1;
            // 
            // RoomEventListBox
            // 
            this.RoomEventListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomEventListBox.FormattingEnabled = true;
            this.RoomEventListBox.Location = new System.Drawing.Point(6, 6);
            this.RoomEventListBox.Name = "RoomEventListBox";
            this.RoomEventListBox.Size = new System.Drawing.Size(139, 238);
            this.RoomEventListBox.TabIndex = 0;
            this.RoomEventListBox.SelectedIndexChanged += new System.EventHandler(this.RoomEventListBox_SelectedIndexChanged);
            // 
            // RoomDescription
            // 
            this.RoomDescription.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RoomDescription.Location = new System.Drawing.Point(208, 57);
            this.RoomDescription.Multiline = true;
            this.RoomDescription.Name = "RoomDescription";
            this.RoomDescription.Size = new System.Drawing.Size(515, 107);
            this.RoomDescription.TabIndex = 4;
            // 
            // LabelRoomDescription
            // 
            this.LabelRoomDescription.AutoSize = true;
            this.LabelRoomDescription.Location = new System.Drawing.Point(205, 41);
            this.LabelRoomDescription.Name = "LabelRoomDescription";
            this.LabelRoomDescription.Size = new System.Drawing.Size(63, 13);
            this.LabelRoomDescription.TabIndex = 3;
            this.LabelRoomDescription.Text = "Description:";
            // 
            // RoomInternalName
            // 
            this.RoomInternalName.Location = new System.Drawing.Point(287, 7);
            this.RoomInternalName.Name = "RoomInternalName";
            this.RoomInternalName.Size = new System.Drawing.Size(172, 20);
            this.RoomInternalName.TabIndex = 2;
            // 
            // LabelInternalRoomName
            // 
            this.LabelInternalRoomName.AutoSize = true;
            this.LabelInternalRoomName.Location = new System.Drawing.Point(205, 10);
            this.LabelInternalRoomName.Name = "LabelInternalRoomName";
            this.LabelInternalRoomName.Size = new System.Drawing.Size(76, 13);
            this.LabelInternalRoomName.TabIndex = 1;
            this.LabelInternalRoomName.Text = "Internal Name:";
            // 
            // RoomListBox
            // 
            this.RoomListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.RoomListBox.FormattingEnabled = true;
            this.RoomListBox.Location = new System.Drawing.Point(7, 7);
            this.RoomListBox.Name = "RoomListBox";
            this.RoomListBox.Size = new System.Drawing.Size(184, 381);
            this.RoomListBox.TabIndex = 0;
            this.RoomListBox.SelectedIndexChanged += new System.EventHandler(this.RoomListBox_SelectedIndexChanged);
            // 
            // ItemsTab
            // 
            this.ItemsTab.Location = new System.Drawing.Point(4, 22);
            this.ItemsTab.Name = "ItemsTab";
            this.ItemsTab.Size = new System.Drawing.Size(729, 450);
            this.ItemsTab.TabIndex = 3;
            this.ItemsTab.Text = "Items";
            this.ItemsTab.UseVisualStyleBackColor = true;
            // 
            // TextTab
            // 
            this.TextTab.Location = new System.Drawing.Point(4, 22);
            this.TextTab.Name = "TextTab";
            this.TextTab.Size = new System.Drawing.Size(729, 450);
            this.TextTab.TabIndex = 2;
            this.TextTab.Text = "Text";
            this.TextTab.UseVisualStyleBackColor = true;
            // 
            // UserTab
            // 
            this.UserTab.Location = new System.Drawing.Point(4, 22);
            this.UserTab.Name = "UserTab";
            this.UserTab.Size = new System.Drawing.Size(729, 450);
            this.UserTab.TabIndex = 4;
            this.UserTab.Text = "User";
            this.UserTab.UseVisualStyleBackColor = true;
            // 
            // PrimaryMenuStrip
            // 
            this.PrimaryMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenuItem});
            this.PrimaryMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.PrimaryMenuStrip.Name = "PrimaryMenuStrip";
            this.PrimaryMenuStrip.Size = new System.Drawing.Size(762, 24);
            this.PrimaryMenuStrip.TabIndex = 1;
            this.PrimaryMenuStrip.Text = "Menus";
            // 
            // FileMenuItem
            // 
            this.FileMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
            this.FileMenuItem.Name = "FileMenuItem";
            this.FileMenuItem.Size = new System.Drawing.Size(37, 20);
            this.FileMenuItem.Text = "&File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.openToolStripMenuItem.Text = "&Open...";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.saveToolStripMenuItem.Text = "&Save...";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(109, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // FolderPicker
            // 
            this.FolderPicker.SelectedPath = global::FormulaEdit.Properties.Settings.Default.LastWorkingPath;
            // 
            // RoomEventLayoutPanel
            // 
            this.RoomEventLayoutPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RoomEventLayoutPanel.AutoScroll = true;
            this.RoomEventLayoutPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RoomEventLayoutPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.RoomEventLayoutPanel.Location = new System.Drawing.Point(151, 32);
            this.RoomEventLayoutPanel.Name = "RoomEventLayoutPanel";
            this.RoomEventLayoutPanel.Size = new System.Drawing.Size(355, 162);
            this.RoomEventLayoutPanel.TabIndex = 3;
            this.RoomEventLayoutPanel.WrapContents = false;
            // 
            // RoomEventNewActionButton
            // 
            this.RoomEventNewActionButton.Location = new System.Drawing.Point(380, 6);
            this.RoomEventNewActionButton.Name = "RoomEventNewActionButton";
            this.RoomEventNewActionButton.Size = new System.Drawing.Size(126, 20);
            this.RoomEventNewActionButton.TabIndex = 4;
            this.RoomEventNewActionButton.Text = "New Action";
            this.RoomEventNewActionButton.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(762, 515);
            this.Controls.Add(this.MainEditorTabs);
            this.Controls.Add(this.PrimaryMenuStrip);
            this.MinimumSize = new System.Drawing.Size(778, 554);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FormulaEdit";
            this.MainEditorTabs.ResumeLayout(false);
            this.CommandsTab.ResumeLayout(false);
            this.CommandsTab.PerformLayout();
            this.RoomsTab.ResumeLayout(false);
            this.RoomsTab.PerformLayout();
            this.RoomTabControls.ResumeLayout(false);
            this.RoomConnectionsTab.ResumeLayout(false);
            this.RoomConnectionsTab.PerformLayout();
            this.RoomListsTab.ResumeLayout(false);
            this.RoomListsTab.PerformLayout();
            this.RoomEventsTab.ResumeLayout(false);
            this.RoomEventsTab.PerformLayout();
            this.PrimaryMenuStrip.ResumeLayout(false);
            this.PrimaryMenuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl MainEditorTabs;
        private System.Windows.Forms.TabPage CommandsTab;
        private System.Windows.Forms.TabPage RoomsTab;
        private System.Windows.Forms.TabPage ItemsTab;
        private System.Windows.Forms.TabPage TextTab;
        private System.Windows.Forms.TabPage UserTab;
        private System.Windows.Forms.ListBox CommandListBox;
        private System.Windows.Forms.Button RemoveCommandButton;
        private System.Windows.Forms.Button AddCommandButton;
        private System.Windows.Forms.MenuStrip PrimaryMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem FileMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TextBox CommandName;
        private System.Windows.Forms.Label LabelCommandFromUser;
        private System.Windows.Forms.Label LabelCommandEvent;
        private System.Windows.Forms.TextBox CommandEventName;
        private System.Windows.Forms.TextBox CommandHelpTextBox;
        private System.Windows.Forms.Label LabelCommandHelpText;
        private System.Windows.Forms.FolderBrowserDialog FolderPicker;
        private System.Windows.Forms.Button CommandApplyButton;
        private System.Windows.Forms.ListBox RoomListBox;
        private System.Windows.Forms.Label LabelInternalRoomName;
        private System.Windows.Forms.TextBox RoomInternalName;
        private System.Windows.Forms.Label LabelRoomDescription;
        private System.Windows.Forms.TextBox RoomDescription;
        private System.Windows.Forms.TabControl RoomTabControls;
        private System.Windows.Forms.TabPage RoomConnectionsTab;
        private System.Windows.Forms.TabPage RoomListsTab;
        private System.Windows.Forms.TabPage RoomEventsTab;
        private System.Windows.Forms.ListBox RoomConnectionsListBox;
        private System.Windows.Forms.Button RoomConnectionApplyButton;
        private System.Windows.Forms.Button RoomConnectionRemoveButton;
        private System.Windows.Forms.Button RoomConnectionAddButton;
        private System.Windows.Forms.ListBox RoomConnectionEndpointListBox;
        private System.Windows.Forms.Label LabelRoomConnectionEndpoint;
        private System.Windows.Forms.Label LabelRoomConnectionDirection;
        private System.Windows.Forms.TextBox RoomConnectionDirection;
        private System.Windows.Forms.ListBox RoomListsListBox;
        private System.Windows.Forms.TextBox RoomListName;
        private System.Windows.Forms.Label LabelRoomListContents;
        private System.Windows.Forms.Label LabelRoomListName;
        private System.Windows.Forms.TextBox RoomListContents;
        private System.Windows.Forms.Button RoomListApplyButton;
        private System.Windows.Forms.Button RoomListRemoveButton;
        private System.Windows.Forms.Button RoomListAddButton;
        private System.Windows.Forms.ListBox RoomEventListBox;
        private System.Windows.Forms.TextBox RoomEventCode;
        private System.Windows.Forms.Label LabelRoomEventCode;
        private System.Windows.Forms.FlowLayoutPanel RoomEventLayoutPanel;
        private System.Windows.Forms.Button RoomEventNewActionButton;
    }
}

