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
    public partial class ScriptActionControlForEach : UserControl
    {
        internal ScriptActionControlForEach(MudData.FormulaActionForEach action)
        {
            InitializeComponent();

            ListComboBox.Text = action.list;

            ScriptActionEditControl.PopulatePanel(action.actions, ActionsFlowPanel);
        }
    }
}
