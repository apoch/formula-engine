namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlIf
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
            this.AddActionButton = new System.Windows.Forms.Button();
            this.LabelActions = new System.Windows.Forms.Label();
            this.ActionsFlowPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.ConditionTextBox = new System.Windows.Forms.TextBox();
            this.LabelCondition = new System.Windows.Forms.Label();
            this.AddElseActionButton = new System.Windows.Forms.Button();
            this.LabelElse = new System.Windows.Forms.Label();
            this.ElseActionsFlowPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.SuspendLayout();
            // 
            // AddActionButton
            // 
            this.AddActionButton.Location = new System.Drawing.Point(84, 29);
            this.AddActionButton.Name = "AddActionButton";
            this.AddActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddActionButton.TabIndex = 8;
            this.AddActionButton.Text = "+";
            this.AddActionButton.UseVisualStyleBackColor = true;
            // 
            // LabelActions
            // 
            this.LabelActions.AutoSize = true;
            this.LabelActions.Location = new System.Drawing.Point(33, 34);
            this.LabelActions.Name = "LabelActions";
            this.LabelActions.Size = new System.Drawing.Size(45, 13);
            this.LabelActions.TabIndex = 7;
            this.LabelActions.Text = "Actions:";
            // 
            // ActionsFlowPanel
            // 
            this.ActionsFlowPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ActionsFlowPanel.AutoSize = true;
            this.ActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ActionsFlowPanel.Location = new System.Drawing.Point(84, 55);
            this.ActionsFlowPanel.Name = "ActionsFlowPanel";
            this.ActionsFlowPanel.Size = new System.Drawing.Size(254, 132);
            this.ActionsFlowPanel.TabIndex = 6;
            // 
            // ConditionTextBox
            // 
            this.ConditionTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ConditionTextBox.Location = new System.Drawing.Point(84, 3);
            this.ConditionTextBox.Name = "ConditionTextBox";
            this.ConditionTextBox.Size = new System.Drawing.Size(254, 20);
            this.ConditionTextBox.TabIndex = 10;
            // 
            // LabelCondition
            // 
            this.LabelCondition.AutoSize = true;
            this.LabelCondition.Location = new System.Drawing.Point(24, 6);
            this.LabelCondition.Name = "LabelCondition";
            this.LabelCondition.Size = new System.Drawing.Size(54, 13);
            this.LabelCondition.TabIndex = 11;
            this.LabelCondition.Text = "Condition:";
            // 
            // AddElseActionButton
            // 
            this.AddElseActionButton.Location = new System.Drawing.Point(84, 195);
            this.AddElseActionButton.Name = "AddElseActionButton";
            this.AddElseActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddElseActionButton.TabIndex = 14;
            this.AddElseActionButton.Text = "+";
            this.AddElseActionButton.UseVisualStyleBackColor = true;
            // 
            // LabelElse
            // 
            this.LabelElse.AutoSize = true;
            this.LabelElse.Location = new System.Drawing.Point(48, 200);
            this.LabelElse.Name = "LabelElse";
            this.LabelElse.Size = new System.Drawing.Size(30, 13);
            this.LabelElse.TabIndex = 13;
            this.LabelElse.Text = "Else:";
            // 
            // ElseActionsFlowPanel
            // 
            this.ElseActionsFlowPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ElseActionsFlowPanel.AutoSize = true;
            this.ElseActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ElseActionsFlowPanel.Location = new System.Drawing.Point(84, 221);
            this.ElseActionsFlowPanel.Name = "ElseActionsFlowPanel";
            this.ElseActionsFlowPanel.Size = new System.Drawing.Size(254, 132);
            this.ElseActionsFlowPanel.TabIndex = 12;
            // 
            // ScriptActionControlIf
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.AddElseActionButton);
            this.Controls.Add(this.LabelElse);
            this.Controls.Add(this.ElseActionsFlowPanel);
            this.Controls.Add(this.LabelCondition);
            this.Controls.Add(this.ConditionTextBox);
            this.Controls.Add(this.AddActionButton);
            this.Controls.Add(this.LabelActions);
            this.Controls.Add(this.ActionsFlowPanel);
            this.Name = "ScriptActionControlIf";
            this.Size = new System.Drawing.Size(341, 361);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button AddActionButton;
        private System.Windows.Forms.Label LabelActions;
        private System.Windows.Forms.FlowLayoutPanel ActionsFlowPanel;
        private System.Windows.Forms.TextBox ConditionTextBox;
        private System.Windows.Forms.Label LabelCondition;
        private System.Windows.Forms.Button AddElseActionButton;
        private System.Windows.Forms.Label LabelElse;
        private System.Windows.Forms.FlowLayoutPanel ElseActionsFlowPanel;
    }
}
