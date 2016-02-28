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
            this.ConditionTextBox = new System.Windows.Forms.TextBox();
            this.LabelCondition = new System.Windows.Forms.Label();
            this.ElasticPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.ElsePanel = new System.Windows.Forms.Panel();
            this.AddElseActionButton = new System.Windows.Forms.Button();
            this.LabelElse = new System.Windows.Forms.Label();
            this.ElseActionsFlowPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.AddActionButton = new System.Windows.Forms.Button();
            this.LabelActions = new System.Windows.Forms.Label();
            this.ActionsFlowPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.ElasticPanel.SuspendLayout();
            this.ElsePanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ConditionTextBox
            // 
            this.ConditionTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ConditionTextBox.Location = new System.Drawing.Point(84, 3);
            this.ConditionTextBox.Name = "ConditionTextBox";
            this.ConditionTextBox.Size = new System.Drawing.Size(260, 20);
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
            // ElasticPanel
            // 
            this.ElasticPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ElasticPanel.AutoSize = true;
            this.ElasticPanel.Controls.Add(this.panel1);
            this.ElasticPanel.Controls.Add(this.ElsePanel);
            this.ElasticPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ElasticPanel.Location = new System.Drawing.Point(4, 29);
            this.ElasticPanel.Name = "ElasticPanel";
            this.ElasticPanel.Size = new System.Drawing.Size(340, 299);
            this.ElasticPanel.TabIndex = 15;
            this.ElasticPanel.WrapContents = false;
            // 
            // ElsePanel
            // 
            this.ElsePanel.AutoSize = true;
            this.ElsePanel.Controls.Add(this.AddElseActionButton);
            this.ElsePanel.Controls.Add(this.LabelElse);
            this.ElsePanel.Controls.Add(this.ElseActionsFlowPanel);
            this.ElsePanel.Location = new System.Drawing.Point(3, 141);
            this.ElsePanel.MinimumSize = new System.Drawing.Size(150, 150);
            this.ElsePanel.Name = "ElsePanel";
            this.ElsePanel.Size = new System.Drawing.Size(331, 150);
            this.ElsePanel.TabIndex = 0;
            // 
            // AddElseActionButton
            // 
            this.AddElseActionButton.Location = new System.Drawing.Point(58, 3);
            this.AddElseActionButton.Name = "AddElseActionButton";
            this.AddElseActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddElseActionButton.TabIndex = 17;
            this.AddElseActionButton.Text = "+";
            this.AddElseActionButton.UseVisualStyleBackColor = true;
            // 
            // LabelElse
            // 
            this.LabelElse.AutoSize = true;
            this.LabelElse.Location = new System.Drawing.Point(17, 8);
            this.LabelElse.Name = "LabelElse";
            this.LabelElse.Size = new System.Drawing.Size(30, 13);
            this.LabelElse.TabIndex = 16;
            this.LabelElse.Text = "Else:";
            // 
            // ElseActionsFlowPanel
            // 
            this.ElseActionsFlowPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ElseActionsFlowPanel.AutoSize = true;
            this.ElseActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ElseActionsFlowPanel.Location = new System.Drawing.Point(58, 31);
            this.ElseActionsFlowPanel.Name = "ElseActionsFlowPanel";
            this.ElseActionsFlowPanel.Size = new System.Drawing.Size(273, 106);
            this.ElseActionsFlowPanel.TabIndex = 15;
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.AddActionButton);
            this.panel1.Controls.Add(this.LabelActions);
            this.panel1.Controls.Add(this.ActionsFlowPanel);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(331, 132);
            this.panel1.TabIndex = 1;
            // 
            // AddActionButton
            // 
            this.AddActionButton.Location = new System.Drawing.Point(58, 6);
            this.AddActionButton.Name = "AddActionButton";
            this.AddActionButton.Size = new System.Drawing.Size(33, 22);
            this.AddActionButton.TabIndex = 11;
            this.AddActionButton.Text = "+";
            this.AddActionButton.UseVisualStyleBackColor = true;
            // 
            // LabelActions
            // 
            this.LabelActions.AutoSize = true;
            this.LabelActions.Location = new System.Drawing.Point(7, 11);
            this.LabelActions.Name = "LabelActions";
            this.LabelActions.Size = new System.Drawing.Size(45, 13);
            this.LabelActions.TabIndex = 10;
            this.LabelActions.Text = "Actions:";
            // 
            // ActionsFlowPanel
            // 
            this.ActionsFlowPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ActionsFlowPanel.AutoSize = true;
            this.ActionsFlowPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.ActionsFlowPanel.Location = new System.Drawing.Point(58, 32);
            this.ActionsFlowPanel.Name = "ActionsFlowPanel";
            this.ActionsFlowPanel.Size = new System.Drawing.Size(270, 97);
            this.ActionsFlowPanel.TabIndex = 9;
            // 
            // ScriptActionControlIf
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.LabelCondition);
            this.Controls.Add(this.ConditionTextBox);
            this.Controls.Add(this.ElasticPanel);
            this.Name = "ScriptActionControlIf";
            this.Size = new System.Drawing.Size(347, 331);
            this.ElasticPanel.ResumeLayout(false);
            this.ElasticPanel.PerformLayout();
            this.ElsePanel.ResumeLayout(false);
            this.ElsePanel.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox ConditionTextBox;
        private System.Windows.Forms.Label LabelCondition;
        private System.Windows.Forms.FlowLayoutPanel ElasticPanel;
        private System.Windows.Forms.Panel ElsePanel;
        private System.Windows.Forms.Button AddElseActionButton;
        private System.Windows.Forms.Label LabelElse;
        private System.Windows.Forms.FlowLayoutPanel ElseActionsFlowPanel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button AddActionButton;
        private System.Windows.Forms.Label LabelActions;
        private System.Windows.Forms.FlowLayoutPanel ActionsFlowPanel;
    }
}
