namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlListRemove
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
            this.FilterConditionTextBox = new System.Windows.Forms.TextBox();
            this.ScriptableComboBox = new System.Windows.Forms.ComboBox();
            this.OriginListComboBox = new System.Windows.Forms.ComboBox();
            this.LabelScriptable = new System.Windows.Forms.Label();
            this.LabelList = new System.Windows.Forms.Label();
            this.LabelFilter = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // FilterConditionTextBox
            // 
            this.FilterConditionTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FilterConditionTextBox.Location = new System.Drawing.Point(65, 57);
            this.FilterConditionTextBox.Name = "FilterConditionTextBox";
            this.FilterConditionTextBox.Size = new System.Drawing.Size(252, 20);
            this.FilterConditionTextBox.TabIndex = 0;
            // 
            // ScriptableComboBox
            // 
            this.ScriptableComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ScriptableComboBox.FormattingEnabled = true;
            this.ScriptableComboBox.Location = new System.Drawing.Point(65, 3);
            this.ScriptableComboBox.Name = "ScriptableComboBox";
            this.ScriptableComboBox.Size = new System.Drawing.Size(252, 21);
            this.ScriptableComboBox.TabIndex = 1;
            // 
            // OriginListComboBox
            // 
            this.OriginListComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.OriginListComboBox.FormattingEnabled = true;
            this.OriginListComboBox.Location = new System.Drawing.Point(65, 30);
            this.OriginListComboBox.Name = "OriginListComboBox";
            this.OriginListComboBox.Size = new System.Drawing.Size(252, 21);
            this.OriginListComboBox.TabIndex = 2;
            // 
            // LabelScriptable
            // 
            this.LabelScriptable.AutoSize = true;
            this.LabelScriptable.Location = new System.Drawing.Point(18, 6);
            this.LabelScriptable.Name = "LabelScriptable";
            this.LabelScriptable.Size = new System.Drawing.Size(41, 13);
            this.LabelScriptable.TabIndex = 3;
            this.LabelScriptable.Text = "Object:";
            // 
            // LabelList
            // 
            this.LabelList.AutoSize = true;
            this.LabelList.Location = new System.Drawing.Point(33, 33);
            this.LabelList.Name = "LabelList";
            this.LabelList.Size = new System.Drawing.Size(26, 13);
            this.LabelList.TabIndex = 4;
            this.LabelList.Text = "List:";
            // 
            // LabelFilter
            // 
            this.LabelFilter.AutoSize = true;
            this.LabelFilter.Location = new System.Drawing.Point(27, 60);
            this.LabelFilter.Name = "LabelFilter";
            this.LabelFilter.Size = new System.Drawing.Size(32, 13);
            this.LabelFilter.TabIndex = 5;
            this.LabelFilter.Text = "Filter:";
            // 
            // ScriptActionControlListRemove
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.LabelFilter);
            this.Controls.Add(this.LabelList);
            this.Controls.Add(this.LabelScriptable);
            this.Controls.Add(this.OriginListComboBox);
            this.Controls.Add(this.ScriptableComboBox);
            this.Controls.Add(this.FilterConditionTextBox);
            this.Name = "ScriptActionControlListRemove";
            this.Size = new System.Drawing.Size(320, 91);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox FilterConditionTextBox;
        private System.Windows.Forms.ComboBox ScriptableComboBox;
        private System.Windows.Forms.ComboBox OriginListComboBox;
        private System.Windows.Forms.Label LabelScriptable;
        private System.Windows.Forms.Label LabelList;
        private System.Windows.Forms.Label LabelFilter;
    }
}
