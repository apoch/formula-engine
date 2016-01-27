namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlForEach
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
            this.ListComboBox = new System.Windows.Forms.ComboBox();
            this.LabelList = new System.Windows.Forms.Label();
            this.ActionsFlowPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.LabelActions = new System.Windows.Forms.Label();
            this.AddActionButton = new System.Windows.Forms.Button();
            this.RemoveActionButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ListComboBox
            // 
            this.ListComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ListComboBox.FormattingEnabled = true;
            this.ListComboBox.Location = new System.Drawing.Point(55, 3);
            this.ListComboBox.Name = "ListComboBox";
            this.ListComboBox.Size = new System.Drawing.Size(228, 21);
            this.ListComboBox.TabIndex = 0;
            // 
            // LabelList
            // 
            this.LabelList.AutoSize = true;
            this.LabelList.Location = new System.Drawing.Point(23, 6);
            this.LabelList.Name = "LabelList";
            this.LabelList.Size = new System.Drawing.Size(26, 13);
            this.LabelList.TabIndex = 1;
            this.LabelList.Text = "List:";
            // 
            // ActionsFlowPanel
            // 
            this.ActionsFlowPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ActionsFlowPanel.AutoSize = true;
            this.ActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ActionsFlowPanel.Location = new System.Drawing.Point(54, 56);
            this.ActionsFlowPanel.Name = "ActionsFlowPanel";
            this.ActionsFlowPanel.Size = new System.Drawing.Size(229, 94);
            this.ActionsFlowPanel.TabIndex = 2;
            // 
            // LabelActions
            // 
            this.LabelActions.AutoSize = true;
            this.LabelActions.Location = new System.Drawing.Point(3, 35);
            this.LabelActions.Name = "LabelActions";
            this.LabelActions.Size = new System.Drawing.Size(45, 13);
            this.LabelActions.TabIndex = 3;
            this.LabelActions.Text = "Actions:";
            // 
            // AddActionButton
            // 
            this.AddActionButton.Location = new System.Drawing.Point(54, 30);
            this.AddActionButton.Name = "AddActionButton";
            this.AddActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddActionButton.TabIndex = 4;
            this.AddActionButton.Text = "+";
            this.AddActionButton.UseVisualStyleBackColor = true;
            // 
            // RemoveActionButton
            // 
            this.RemoveActionButton.Location = new System.Drawing.Point(93, 30);
            this.RemoveActionButton.Name = "RemoveActionButton";
            this.RemoveActionButton.Size = new System.Drawing.Size(33, 22);
            this.RemoveActionButton.TabIndex = 5;
            this.RemoveActionButton.Text = "-";
            this.RemoveActionButton.UseVisualStyleBackColor = true;
            // 
            // ScriptActionControlForEach
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.RemoveActionButton);
            this.Controls.Add(this.AddActionButton);
            this.Controls.Add(this.LabelActions);
            this.Controls.Add(this.ActionsFlowPanel);
            this.Controls.Add(this.LabelList);
            this.Controls.Add(this.ListComboBox);
            this.MinimumSize = new System.Drawing.Size(286, 153);
            this.Name = "ScriptActionControlForEach";
            this.Size = new System.Drawing.Size(286, 153);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox ListComboBox;
        private System.Windows.Forms.Label LabelList;
        private System.Windows.Forms.FlowLayoutPanel ActionsFlowPanel;
        private System.Windows.Forms.Label LabelActions;
        private System.Windows.Forms.Button AddActionButton;
        private System.Windows.Forms.Button RemoveActionButton;
    }
}
