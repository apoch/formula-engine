namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlTriggerEvent
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ParamDataGridView = new System.Windows.Forms.DataGridView();
            this.ParamNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ParamValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TargetComboBox = new System.Windows.Forms.ComboBox();
            this.LabelTarget = new System.Windows.Forms.Label();
            this.EventComboBox = new System.Windows.Forms.ComboBox();
            this.LabelEvent = new System.Windows.Forms.Label();
            this.LabelDelay = new System.Windows.Forms.Label();
            this.DelayTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.ParamDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // ParamDataGridView
            // 
            this.ParamDataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ParamDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.ParamDataGridView.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.ParamDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ParamDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ParamNameColumn,
            this.ParamValueColumn});
            this.ParamDataGridView.Location = new System.Drawing.Point(79, 91);
            this.ParamDataGridView.Name = "ParamDataGridView";
            this.ParamDataGridView.Size = new System.Drawing.Size(231, 146);
            this.ParamDataGridView.TabIndex = 5;
            // 
            // ParamNameColumn
            // 
            this.ParamNameColumn.HeaderText = "Param Name";
            this.ParamNameColumn.Name = "ParamNameColumn";
            this.ParamNameColumn.Width = 93;
            // 
            // ParamValueColumn
            // 
            this.ParamValueColumn.HeaderText = "Value";
            this.ParamValueColumn.Name = "ParamValueColumn";
            this.ParamValueColumn.Width = 59;
            // 
            // TargetComboBox
            // 
            this.TargetComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TargetComboBox.FormattingEnabled = true;
            this.TargetComboBox.Location = new System.Drawing.Point(79, 3);
            this.TargetComboBox.Name = "TargetComboBox";
            this.TargetComboBox.Size = new System.Drawing.Size(231, 21);
            this.TargetComboBox.TabIndex = 6;
            // 
            // LabelTarget
            // 
            this.LabelTarget.AutoSize = true;
            this.LabelTarget.Location = new System.Drawing.Point(32, 6);
            this.LabelTarget.Name = "LabelTarget";
            this.LabelTarget.Size = new System.Drawing.Size(41, 13);
            this.LabelTarget.TabIndex = 7;
            this.LabelTarget.Text = "Target:";
            // 
            // EventComboBox
            // 
            this.EventComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.EventComboBox.FormattingEnabled = true;
            this.EventComboBox.Location = new System.Drawing.Point(79, 31);
            this.EventComboBox.Name = "EventComboBox";
            this.EventComboBox.Size = new System.Drawing.Size(231, 21);
            this.EventComboBox.TabIndex = 8;
            // 
            // LabelEvent
            // 
            this.LabelEvent.AutoSize = true;
            this.LabelEvent.Location = new System.Drawing.Point(35, 34);
            this.LabelEvent.Name = "LabelEvent";
            this.LabelEvent.Size = new System.Drawing.Size(38, 13);
            this.LabelEvent.TabIndex = 9;
            this.LabelEvent.Text = "Event:";
            // 
            // LabelDelay
            // 
            this.LabelDelay.AutoSize = true;
            this.LabelDelay.Location = new System.Drawing.Point(36, 61);
            this.LabelDelay.Name = "LabelDelay";
            this.LabelDelay.Size = new System.Drawing.Size(37, 13);
            this.LabelDelay.TabIndex = 10;
            this.LabelDelay.Text = "Delay:";
            // 
            // DelayTextBox
            // 
            this.DelayTextBox.Location = new System.Drawing.Point(79, 58);
            this.DelayTextBox.Name = "DelayTextBox";
            this.DelayTextBox.Size = new System.Drawing.Size(126, 20);
            this.DelayTextBox.TabIndex = 11;
            // 
            // ScriptActionControlTriggerEvent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.DelayTextBox);
            this.Controls.Add(this.LabelDelay);
            this.Controls.Add(this.LabelEvent);
            this.Controls.Add(this.EventComboBox);
            this.Controls.Add(this.LabelTarget);
            this.Controls.Add(this.TargetComboBox);
            this.Controls.Add(this.ParamDataGridView);
            this.Name = "ScriptActionControlTriggerEvent";
            this.Size = new System.Drawing.Size(313, 240);
            ((System.ComponentModel.ISupportInitialize)(this.ParamDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView ParamDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn ParamNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ParamValueColumn;
        private System.Windows.Forms.ComboBox TargetComboBox;
        private System.Windows.Forms.Label LabelTarget;
        private System.Windows.Forms.ComboBox EventComboBox;
        private System.Windows.Forms.Label LabelEvent;
        private System.Windows.Forms.Label LabelDelay;
        private System.Windows.Forms.TextBox DelayTextBox;
    }
}
