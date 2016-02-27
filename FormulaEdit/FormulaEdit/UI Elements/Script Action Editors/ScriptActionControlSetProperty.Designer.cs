namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlSetProperty
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
            this.PropertyComboBox = new System.Windows.Forms.ComboBox();
            this.LabelProperty = new System.Windows.Forms.Label();
            this.FormulaTextBox = new System.Windows.Forms.TextBox();
            this.LabelFormula = new System.Windows.Forms.Label();
            this.ObjectComboBox = new System.Windows.Forms.ComboBox();
            this.LabelObject = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // PropertyComboBox
            // 
            this.PropertyComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PropertyComboBox.FormattingEnabled = true;
            this.PropertyComboBox.Location = new System.Drawing.Point(74, 3);
            this.PropertyComboBox.Name = "PropertyComboBox";
            this.PropertyComboBox.Size = new System.Drawing.Size(196, 21);
            this.PropertyComboBox.TabIndex = 0;
            // 
            // LabelProperty
            // 
            this.LabelProperty.AutoSize = true;
            this.LabelProperty.Location = new System.Drawing.Point(19, 6);
            this.LabelProperty.Name = "LabelProperty";
            this.LabelProperty.Size = new System.Drawing.Size(49, 13);
            this.LabelProperty.TabIndex = 1;
            this.LabelProperty.Text = "Property:";
            // 
            // FormulaTextBox
            // 
            this.FormulaTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FormulaTextBox.Location = new System.Drawing.Point(74, 30);
            this.FormulaTextBox.Name = "FormulaTextBox";
            this.FormulaTextBox.Size = new System.Drawing.Size(196, 20);
            this.FormulaTextBox.TabIndex = 2;
            // 
            // LabelFormula
            // 
            this.LabelFormula.AutoSize = true;
            this.LabelFormula.Location = new System.Drawing.Point(31, 33);
            this.LabelFormula.Name = "LabelFormula";
            this.LabelFormula.Size = new System.Drawing.Size(37, 13);
            this.LabelFormula.TabIndex = 3;
            this.LabelFormula.Text = "Value:";
            // 
            // ObjectComboBox
            // 
            this.ObjectComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ObjectComboBox.FormattingEnabled = true;
            this.ObjectComboBox.Location = new System.Drawing.Point(74, 56);
            this.ObjectComboBox.Name = "ObjectComboBox";
            this.ObjectComboBox.Size = new System.Drawing.Size(196, 21);
            this.ObjectComboBox.TabIndex = 4;
            // 
            // LabelObject
            // 
            this.LabelObject.AutoSize = true;
            this.LabelObject.Location = new System.Drawing.Point(27, 59);
            this.LabelObject.Name = "LabelObject";
            this.LabelObject.Size = new System.Drawing.Size(41, 13);
            this.LabelObject.TabIndex = 5;
            this.LabelObject.Text = "Object:";
            // 
            // ScriptActionControlSetProperty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.LabelObject);
            this.Controls.Add(this.ObjectComboBox);
            this.Controls.Add(this.LabelFormula);
            this.Controls.Add(this.FormulaTextBox);
            this.Controls.Add(this.LabelProperty);
            this.Controls.Add(this.PropertyComboBox);
            this.Name = "ScriptActionControlSetProperty";
            this.Size = new System.Drawing.Size(273, 81);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox PropertyComboBox;
        private System.Windows.Forms.Label LabelProperty;
        private System.Windows.Forms.TextBox FormulaTextBox;
        private System.Windows.Forms.Label LabelFormula;
        private System.Windows.Forms.ComboBox ObjectComboBox;
        private System.Windows.Forms.Label LabelObject;
    }
}
