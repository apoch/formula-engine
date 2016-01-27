namespace FormulaEdit
{
    partial class ScriptActionEditControl
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
            this.LabelAction = new System.Windows.Forms.Label();
            this.ActionComboBox = new System.Windows.Forms.ComboBox();
            this.ContainerPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.SuspendLayout();
            // 
            // LabelAction
            // 
            this.LabelAction.AutoSize = true;
            this.LabelAction.Location = new System.Drawing.Point(3, 6);
            this.LabelAction.Name = "LabelAction";
            this.LabelAction.Size = new System.Drawing.Size(40, 13);
            this.LabelAction.TabIndex = 0;
            this.LabelAction.Text = "Action:";
            // 
            // ActionComboBox
            // 
            this.ActionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ActionComboBox.FormattingEnabled = true;
            this.ActionComboBox.Items.AddRange(new object[] {
            "if",
            "foreach",
            "AddSelfToList",
            "CreateListMember",
            "ListTransfer",
            "RepeatEvent",
            "SetGoalState",
            "SetProperty",
            "TriggerEvent"});
            this.ActionComboBox.Location = new System.Drawing.Point(49, 3);
            this.ActionComboBox.Name = "ActionComboBox";
            this.ActionComboBox.Size = new System.Drawing.Size(167, 21);
            this.ActionComboBox.TabIndex = 1;
            // 
            // ContainerPanel
            // 
            this.ContainerPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ContainerPanel.AutoSize = true;
            this.ContainerPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ContainerPanel.Location = new System.Drawing.Point(8, 30);
            this.ContainerPanel.Name = "ContainerPanel";
            this.ContainerPanel.Size = new System.Drawing.Size(245, 60);
            this.ContainerPanel.TabIndex = 2;
            // 
            // ScriptActionEditControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.ContainerPanel);
            this.Controls.Add(this.ActionComboBox);
            this.Controls.Add(this.LabelAction);
            this.MinimumSize = new System.Drawing.Size(259, 96);
            this.Name = "ScriptActionEditControl";
            this.Size = new System.Drawing.Size(259, 96);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label LabelAction;
        private System.Windows.Forms.ComboBox ActionComboBox;
        private System.Windows.Forms.FlowLayoutPanel ContainerPanel;
    }
}
