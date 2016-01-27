namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlSetGoalState
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
            this.BindingComboBox = new System.Windows.Forms.ComboBox();
            this.LabelBinding = new System.Windows.Forms.Label();
            this.LabelProperty = new System.Windows.Forms.Label();
            this.PropertyComboBox = new System.Windows.Forms.ComboBox();
            this.ValueTextBox = new System.Windows.Forms.TextBox();
            this.LabelValue = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // BindingComboBox
            // 
            this.BindingComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.BindingComboBox.FormattingEnabled = true;
            this.BindingComboBox.Location = new System.Drawing.Point(66, 3);
            this.BindingComboBox.Name = "BindingComboBox";
            this.BindingComboBox.Size = new System.Drawing.Size(200, 21);
            this.BindingComboBox.TabIndex = 0;
            // 
            // LabelBinding
            // 
            this.LabelBinding.AutoSize = true;
            this.LabelBinding.Location = new System.Drawing.Point(15, 6);
            this.LabelBinding.Name = "LabelBinding";
            this.LabelBinding.Size = new System.Drawing.Size(45, 13);
            this.LabelBinding.TabIndex = 1;
            this.LabelBinding.Text = "Binding:";
            // 
            // LabelProperty
            // 
            this.LabelProperty.AutoSize = true;
            this.LabelProperty.Location = new System.Drawing.Point(11, 33);
            this.LabelProperty.Name = "LabelProperty";
            this.LabelProperty.Size = new System.Drawing.Size(49, 13);
            this.LabelProperty.TabIndex = 2;
            this.LabelProperty.Text = "Property:";
            // 
            // PropertyComboBox
            // 
            this.PropertyComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PropertyComboBox.FormattingEnabled = true;
            this.PropertyComboBox.Location = new System.Drawing.Point(66, 30);
            this.PropertyComboBox.Name = "PropertyComboBox";
            this.PropertyComboBox.Size = new System.Drawing.Size(200, 21);
            this.PropertyComboBox.TabIndex = 3;
            // 
            // ValueTextBox
            // 
            this.ValueTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ValueTextBox.Location = new System.Drawing.Point(66, 57);
            this.ValueTextBox.Name = "ValueTextBox";
            this.ValueTextBox.Size = new System.Drawing.Size(200, 20);
            this.ValueTextBox.TabIndex = 4;
            // 
            // LabelValue
            // 
            this.LabelValue.AutoSize = true;
            this.LabelValue.Location = new System.Drawing.Point(23, 60);
            this.LabelValue.Name = "LabelValue";
            this.LabelValue.Size = new System.Drawing.Size(37, 13);
            this.LabelValue.TabIndex = 5;
            this.LabelValue.Text = "Value:";
            // 
            // ScriptActionControlSetGoalState
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.LabelValue);
            this.Controls.Add(this.ValueTextBox);
            this.Controls.Add(this.PropertyComboBox);
            this.Controls.Add(this.LabelProperty);
            this.Controls.Add(this.LabelBinding);
            this.Controls.Add(this.BindingComboBox);
            this.MinimumSize = new System.Drawing.Size(269, 85);
            this.Name = "ScriptActionControlSetGoalState";
            this.Size = new System.Drawing.Size(269, 85);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox BindingComboBox;
        private System.Windows.Forms.Label LabelBinding;
        private System.Windows.Forms.Label LabelProperty;
        private System.Windows.Forms.ComboBox PropertyComboBox;
        private System.Windows.Forms.TextBox ValueTextBox;
        private System.Windows.Forms.Label LabelValue;
    }
}
