namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlAddSelfToList
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
            this.LabelTarget = new System.Windows.Forms.Label();
            this.LabelList = new System.Windows.Forms.Label();
            this.TargetComboBox = new System.Windows.Forms.ComboBox();
            this.ListComboBox = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // LabelTarget
            // 
            this.LabelTarget.AutoSize = true;
            this.LabelTarget.Location = new System.Drawing.Point(3, 11);
            this.LabelTarget.Name = "LabelTarget";
            this.LabelTarget.Size = new System.Drawing.Size(41, 13);
            this.LabelTarget.TabIndex = 0;
            this.LabelTarget.Text = "Target:";
            // 
            // LabelList
            // 
            this.LabelList.AutoSize = true;
            this.LabelList.Location = new System.Drawing.Point(18, 40);
            this.LabelList.Name = "LabelList";
            this.LabelList.Size = new System.Drawing.Size(26, 13);
            this.LabelList.TabIndex = 1;
            this.LabelList.Text = "List:";
            // 
            // TargetComboBox
            // 
            this.TargetComboBox.FormattingEnabled = true;
            this.TargetComboBox.Location = new System.Drawing.Point(50, 8);
            this.TargetComboBox.Name = "TargetComboBox";
            this.TargetComboBox.Size = new System.Drawing.Size(167, 21);
            this.TargetComboBox.TabIndex = 2;
            // 
            // ListComboBox
            // 
            this.ListComboBox.FormattingEnabled = true;
            this.ListComboBox.Location = new System.Drawing.Point(50, 37);
            this.ListComboBox.Name = "ListComboBox";
            this.ListComboBox.Size = new System.Drawing.Size(167, 21);
            this.ListComboBox.TabIndex = 3;
            // 
            // ScriptActionControlAddSelfToList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ListComboBox);
            this.Controls.Add(this.TargetComboBox);
            this.Controls.Add(this.LabelList);
            this.Controls.Add(this.LabelTarget);
            this.Name = "ScriptActionControlAddSelfToList";
            this.Size = new System.Drawing.Size(220, 69);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label LabelTarget;
        private System.Windows.Forms.Label LabelList;
        private System.Windows.Forms.ComboBox TargetComboBox;
        private System.Windows.Forms.ComboBox ListComboBox;
    }
}
