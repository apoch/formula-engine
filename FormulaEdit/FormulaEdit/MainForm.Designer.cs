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
            this.RoomsTab = new System.Windows.Forms.TabPage();
            this.TextTab = new System.Windows.Forms.TabPage();
            this.ItemsTab = new System.Windows.Forms.TabPage();
            this.UserTab = new System.Windows.Forms.TabPage();
            this.CommandListBox = new System.Windows.Forms.ListBox();
            this.AddCommandButton = new System.Windows.Forms.Button();
            this.RemoveCommandButton = new System.Windows.Forms.Button();
            this.MainMenuStrip = new System.Windows.Forms.MenuStrip();
            this.FileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MainEditorTabs.SuspendLayout();
            this.CommandsTab.SuspendLayout();
            this.MainMenuStrip.SuspendLayout();
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
            // RoomsTab
            // 
            this.RoomsTab.Location = new System.Drawing.Point(4, 22);
            this.RoomsTab.Name = "RoomsTab";
            this.RoomsTab.Padding = new System.Windows.Forms.Padding(3);
            this.RoomsTab.Size = new System.Drawing.Size(729, 464);
            this.RoomsTab.TabIndex = 1;
            this.RoomsTab.Text = "Rooms";
            this.RoomsTab.UseVisualStyleBackColor = true;
            // 
            // TextTab
            // 
            this.TextTab.Location = new System.Drawing.Point(4, 22);
            this.TextTab.Name = "TextTab";
            this.TextTab.Size = new System.Drawing.Size(729, 464);
            this.TextTab.TabIndex = 2;
            this.TextTab.Text = "Text";
            this.TextTab.UseVisualStyleBackColor = true;
            // 
            // ItemsTab
            // 
            this.ItemsTab.Location = new System.Drawing.Point(4, 22);
            this.ItemsTab.Name = "ItemsTab";
            this.ItemsTab.Size = new System.Drawing.Size(729, 464);
            this.ItemsTab.TabIndex = 3;
            this.ItemsTab.Text = "Items";
            this.ItemsTab.UseVisualStyleBackColor = true;
            // 
            // UserTab
            // 
            this.UserTab.Location = new System.Drawing.Point(4, 22);
            this.UserTab.Name = "UserTab";
            this.UserTab.Size = new System.Drawing.Size(729, 464);
            this.UserTab.TabIndex = 4;
            this.UserTab.Text = "User";
            this.UserTab.UseVisualStyleBackColor = true;
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
            // 
            // MainMenuStrip
            // 
            this.MainMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenuItem});
            this.MainMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MainMenuStrip.Name = "MainMenuStrip";
            this.MainMenuStrip.Size = new System.Drawing.Size(762, 24);
            this.MainMenuStrip.TabIndex = 1;
            this.MainMenuStrip.Text = "Menus";
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
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "&Open...";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(762, 515);
            this.Controls.Add(this.MainEditorTabs);
            this.Controls.Add(this.MainMenuStrip);
            this.MainMenuStrip = this.MainMenuStrip;
            this.Name = "MainForm";
            this.Text = "FormulaEdit";
            this.MainEditorTabs.ResumeLayout(false);
            this.CommandsTab.ResumeLayout(false);
            this.MainMenuStrip.ResumeLayout(false);
            this.MainMenuStrip.PerformLayout();
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
        private System.Windows.Forms.MenuStrip MainMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem FileMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    }
}

