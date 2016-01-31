using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormulaEdit.UI_Elements.Script_Action_Editors
{
    public partial class ScriptActionControlListTransfer : UserControl
    {
        internal ScriptActionControlListTransfer(MudData.FormulaActionListTransfer action)
        {
            InitializeComponent();

            ScriptableComboBox.Text = action.scriptable;
            OriginListComboBox.Text = action.list;
            TargetComboBox.Text = action.target;
            TargetListComboBox.Text = action.targetList;
            FilterConditionTextBox.Text = action.condition;
        }
    }
}
