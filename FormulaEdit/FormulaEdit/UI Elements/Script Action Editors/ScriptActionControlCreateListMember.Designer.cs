namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    partial class ScriptActionControlCreateListMember
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
            this.LabelArchetype = new System.Windows.Forms.Label();
            this.ArchetypeComboBox = new System.Windows.Forms.ComboBox();
            this.ParamDataGridView = new System.Windows.Forms.DataGridView();
            this.ParamNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ParamValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.ParamDataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // ListComboBox
            // 
            this.ListComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ListComboBox.FormattingEnabled = true;
            this.ListComboBox.Location = new System.Drawing.Point(79, 3);
            this.ListComboBox.Name = "ListComboBox";
            this.ListComboBox.Size = new System.Drawing.Size(231, 21);
            this.ListComboBox.TabIndex = 0;
            // 
            // LabelList
            // 
            this.LabelList.AutoSize = true;
            this.LabelList.Location = new System.Drawing.Point(47, 6);
            this.LabelList.Name = "LabelList";
            this.LabelList.Size = new System.Drawing.Size(26, 13);
            this.LabelList.TabIndex = 1;
            this.LabelList.Text = "List:";
            // 
            // LabelArchetype
            // 
            this.LabelArchetype.AutoSize = true;
            this.LabelArchetype.Location = new System.Drawing.Point(15, 33);
            this.LabelArchetype.Name = "LabelArchetype";
            this.LabelArchetype.Size = new System.Drawing.Size(58, 13);
            this.LabelArchetype.TabIndex = 2;
            this.LabelArchetype.Text = "Archetype:";
            // 
            // ArchetypeComboBox
            // 
            this.ArchetypeComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ArchetypeComboBox.FormattingEnabled = true;
            this.ArchetypeComboBox.Location = new System.Drawing.Point(79, 30);
            this.ArchetypeComboBox.Name = "ArchetypeComboBox";
            this.ArchetypeComboBox.Size = new System.Drawing.Size(231, 21);
            this.ArchetypeComboBox.TabIndex = 3;
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
            this.ParamDataGridView.Location = new System.Drawing.Point(79, 57);
            this.ParamDataGridView.Name = "ParamDataGridView";
            this.ParamDataGridView.Size = new System.Drawing.Size(231, 95);
            this.ParamDataGridView.TabIndex = 4;
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
            // ScriptActionControlCreateListMember
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.ParamDataGridView);
            this.Controls.Add(this.ArchetypeComboBox);
            this.Controls.Add(this.LabelArchetype);
            this.Controls.Add(this.LabelList);
            this.Controls.Add(this.ListComboBox);
            this.Name = "ScriptActionControlCreateListMember";
            this.Size = new System.Drawing.Size(313, 155);
            ((System.ComponentModel.ISupportInitialize)(this.ParamDataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox ListComboBox;
        private System.Windows.Forms.Label LabelList;
        private System.Windows.Forms.Label LabelArchetype;
        private System.Windows.Forms.ComboBox ArchetypeComboBox;
        private System.Windows.Forms.DataGridView ParamDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn ParamNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ParamValueColumn;
    }
}
