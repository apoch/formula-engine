using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using FormulaEdit.UI_Elements.Script_Action_Editors;


namespace FormulaEdit
{
    public partial class ScriptActionEditControl : UserControl
    {
        public ScriptActionEditControl()
        {
            InitializeComponent();
        }

        internal ScriptActionEditControl(MudData.FormulaAction containerAction)
        {
            InitializeComponent();

            ActionComboBox.SelectedItem = containerAction.action;

            Control ctl = null;
            MudData.FormulaAction action = containerAction.InternalAction;
            if (action == null)
                action = containerAction;

            if (action.GetType() == typeof(MudData.FormulaActionAddSelfToList))
            {
                ctl = new ScriptActionControlAddSelfToList(action as MudData.FormulaActionAddSelfToList);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionCreateListMember))
            {
                // TODO
            }
            else if (action.GetType() == typeof(MudData.FormulaActionIf))
            {
                // TODO
            }
            else if (action.GetType() == typeof(MudData.FormulaActionForEach))
            {
                ctl = new ScriptActionControlForEach(action as MudData.FormulaActionForEach);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionSetGoalState))
            {
                ctl = new ScriptActionControlSetGoalState(action as MudData.FormulaActionSetGoalState);
            }

            if (ctl != null)
            {
                ContainerPanel.Controls.Add(ctl);
                ctl.Dock = DockStyle.Top;
            }
        }

        private MudData.FormulaAction PopulateActionDictionary()
        {
            var ret = new MudData.FormulaAction();

            ret.action = ActionComboBox.Text;

            // TODO - capture stuff from grid!

            return ret;
        }


        internal static void PopulatePanel(List<MudData.FormulaAction> actions, Panel panel)
        {
            foreach (var action in actions)
            {
                var editor = new ScriptActionEditControl(action);
                panel.Controls.Add(editor);

                editor.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
                editor.AutoSize = true;
            }

            panel.Refresh();
        }

        internal static List<MudData.FormulaAction> PopulateMudData(ContainerControl.ControlCollection controls)
        {
            var ret = new List<MudData.FormulaAction>();

            foreach (ScriptActionEditControl ctl in controls)
            {
                ret.Add(ctl.PopulateActionDictionary());
            }

            return ret;
        }
    }
}
