using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormulaEdit
{
    public partial class MainForm : Form
    {
        MudData CurrentLoadedData = null;


        public MainForm()
        {
            InitializeComponent();

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
    }
}
