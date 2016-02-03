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
            this.ScriptableComboBox = new System.Windows.Forms.ComboBox();
            this.LabelScriptable = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ListComboBox
            // 
            this.ListComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ListComboBox.FormattingEnabled = true;
            this.ListComboBox.Location = new System.Drawing.Point(66, 3);
            this.ListComboBox.Name = "ListComboBox";
            this.ListComboBox.Size = new System.Drawing.Size(254, 21);
            this.ListComboBox.TabIndex = 0;
            // 
            // LabelList
            // 
            this.LabelList.AutoSize = true;
            this.LabelList.Location = new System.Drawing.Point(34, 6);
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
            this.ActionsFlowPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ActionsFlowPanel.Location = new System.Drawing.Point(66, 91);
            this.ActionsFlowPanel.MinimumSize = new System.Drawing.Size(229, 94);
            this.ActionsFlowPanel.Name = "ActionsFlowPanel";
            this.ActionsFlowPanel.Size = new System.Drawing.Size(229, 94);
            this.ActionsFlowPanel.TabIndex = 2;
            this.ActionsFlowPanel.WrapContents = false;
            // 
            // LabelActions
            // 
            this.LabelActions.AutoSize = true;
            this.LabelActions.Location = new System.Drawing.Point(15, 69);
            this.LabelActions.Name = "LabelActions";
            this.LabelActions.Size = new System.Drawing.Size(45, 13);
            this.LabelActions.TabIndex = 3;
            this.LabelActions.Text = "Actions:";
            // 
            // AddActionButton
            // 
            this.AddActionButton.Location = new System.Drawing.Point(66, 64);
            this.AddActionButton.Name = "AddActionButton";
            this.AddActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddActionButton.TabIndex = 4;
            this.AddActionButton.Text = "+";
            this.AddActionButton.UseVisualStyleBackColor = true;
            this.AddActionButton.Click += new System.EventHandler(this.AddActionButton_Click);
            // 
            // ScriptableComboBox
            // 
            this.ScriptableComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ScriptableComboBox.FormattingEnabled = true;
            this.ScriptableComboBox.Location = new System.Drawing.Point(66, 30);
            this.ScriptableComboBox.Name = "ScriptableComboBox";
            this.ScriptableComboBox.Size = new System.Drawing.Size(254, 21);
            this.ScriptableComboBox.TabIndex = 5;
            // 
            // LabelScriptable
            // 
            this.LabelScriptable.AutoSize = true;
            this.LabelScriptable.Location = new System.Drawing.Point(3, 33);
            this.LabelScriptable.Name = "LabelScriptable";
            this.LabelScriptable.Size = new System.Drawing.Size(57, 13);
            this.LabelScriptable.TabIndex = 6;
            this.LabelScriptable.Text = "Scriptable:";
            // 
            // ScriptActionControlForEach
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Controls.Add(this.LabelScriptable);
            this.Controls.Add(this.ScriptableComboBox);
            this.Controls.Add(this.AddActionButton);
            this.Controls.Add(this.LabelActions);
            this.Controls.Add(this.ActionsFlowPanel);
            this.Controls.Add(this.LabelList);
            this.Controls.Add(this.ListComboBox);
            this.MinimumSize = new System.Drawing.Size(286, 153);
            this.Name = "ScriptActionControlForEach";
            this.Size = new System.Drawing.Size(323, 188);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox ListComboBox;
        private System.Windows.Forms.Label LabelList;
        private System.Windows.Forms.FlowLayoutPanel ActionsFlowPanel;
        private System.Windows.Forms.Label LabelActions;
        private System.Windows.Forms.Button AddActionButton;
        private System.Windows.Forms.ComboBox ScriptableComboBox;
        private System.Windows.Forms.Label LabelScriptable;
    }
}
