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
    public partial class ScriptActionControlListRemove : UserControl
    {
        internal ScriptActionControlListRemove(MudData.FormulaActionListRemove action)
        {
            InitializeComponent();

            ScriptableComboBox.Text = action.scriptable;
            OriginListComboBox.Text = action.list;
            FilterConditionTextBox.Text = action.condition;
        }

        internal MudData.FormulaActionListRemove GenerateMudDataAction()
        {
            var ret = new MudData.FormulaActionListRemove();
            ret.action = "ListRemove";
            ret.condition = FilterConditionTextBox.Text;
            ret.list = OriginListComboBox.Text;
            ret.scriptable = ScriptableComboBox.Text;

            return ret;
        }
    }
}
