﻿using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlSetProperty : UserControl
    {
        internal ScriptActionControlSetProperty(MudData.FormulaActionSetProperty action)
        {
            InitializeComponent();

            PropertyComboBox.Text = action.property;
            FormulaTextBox.Text = action.value;
            ObjectComboBox.Text = action.target;
        }

        internal MudData.FormulaActionSetProperty GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionSetProperty();
            ret.action = "SetProperty";
            ret.property = PropertyComboBox.Text;
            ret.value = FormulaTextBox.Text;
            ret.target = ObjectComboBox.Text;

            return ret;
        }
    }
}
