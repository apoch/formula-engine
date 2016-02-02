using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

using FormulaEdit.UI_Elements.Script_Action_Editors;


namespace FormulaEdit
{
    public partial class ScriptActionEditControl : UserControl
    {
        public ScriptActionEditControl()
        {
            InitializeComponent();

            Paint += ScriptActionEditControl_Paint;
        }

        internal ScriptActionEditControl(MudData.FormulaAction containerAction)
        {
            InitializeComponent();

            ActionComboBox.SelectedItem = containerAction.action;
            CreateEditorControls(containerAction);

            Paint += ScriptActionEditControl_Paint;
        }

        private MudData.FormulaAction PopulateActionDictionary()
        {
            MudData.FormulaAction action = null;

            if (ActionComboBox.Text == "AddSelfToList")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlAddSelfToList;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "CreateListMember")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlCreateListMember;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "foreach")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlForEach;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "if")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlIf;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "ListTransfer")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlListTransfer;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "RepeatEvent")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlRepeatEvent;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "SetGoalState")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlSetGoalState;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "SetProperty")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlSetProperty;
                action = ctl.GenerateMudDataAction();
            }
            else if (ActionComboBox.Text == "TriggerEvent")
            {
                var ctl = ContainerPanel.Controls[0] as ScriptActionControlTriggerEvent;
                action = ctl.GenerateMudDataAction();
            }
            else
            {
                action = null;
            }

            var ret = new MudData.FormulaAction();
            ret.action = ActionComboBox.Text;
            ret.InternalAction = action;

            return ret;
        }


        private void ScriptActionEditControl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawLine(Pens.Black, 0, 0, Width, 0);
        }


        internal static void PopulatePanel(List<MudData.FormulaAction> actions, FlowLayoutPanel panel)
        {
            foreach (var action in actions)
            {
                var editor = new ScriptActionEditControl(action);
                panel.Controls.Add(editor);
            }

            panel.PerformLayout();
            Utilities.ResizeControls(panel);
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

        private void ActionComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            MudData.FormulaAction action = GetRawActionFromDropdownSelection();
            CreateEditorControls(action);
        }

        private void CreateEditorControls(MudData.FormulaAction containerAction)
        {
            ContainerPanel.Controls.Clear();

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
                ctl = new ScriptActionControlCreateListMember(action as MudData.FormulaActionCreateListMember);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionForEach))
            {
                ctl = new ScriptActionControlForEach(action as MudData.FormulaActionForEach);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionIf))
            {
                ctl = new ScriptActionControlIf(action as MudData.FormulaActionIf);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionListTransfer))
            {
                ctl = new ScriptActionControlListTransfer(action as MudData.FormulaActionListTransfer);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionRepeatEvent))
            {
                ctl = new ScriptActionControlRepeatEvent(action as MudData.FormulaActionRepeatEvent);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionSetGoalState))
            {
                ctl = new ScriptActionControlSetGoalState(action as MudData.FormulaActionSetGoalState);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionSetProperty))
            {
                ctl = new ScriptActionControlSetProperty(action as MudData.FormulaActionSetProperty);
            }
            else if (action.GetType() == typeof(MudData.FormulaActionTriggerEvent))
            {
                ctl = new ScriptActionControlTriggerEvent(action as MudData.FormulaActionTriggerEvent);
            }

            if (ctl != null)
            {
                ContainerPanel.Controls.Add(ctl);
                ctl.Dock = DockStyle.Fill;
            }
            else
            {
                MessageBox.Show("Missing support for actions of this type: " + action.GetType().ToString(), "FormulaEdit", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private MudData.FormulaAction GetRawActionFromDropdownSelection()
        {
            MudData.FormulaAction action = null;

            if (ActionComboBox.Text == "AddSelfToList")
            {
                action = new MudData.FormulaActionAddSelfToList();
            }
            else if (ActionComboBox.Text == "CreateListMember")
            {
                action = new MudData.FormulaActionCreateListMember();
            }
            else if (ActionComboBox.Text == "foreach")
            {
                action = new MudData.FormulaActionForEach();
            }
            else if (ActionComboBox.Text == "if")
            {
                action = new MudData.FormulaActionIf();
            }
            else if (ActionComboBox.Text == "ListTransfer")
            {
                action = new MudData.FormulaActionListTransfer();
            }
            else if (ActionComboBox.Text == "RepeatEvent")
            {
                action = new MudData.FormulaActionRepeatEvent();
            }
            else if (ActionComboBox.Text == "SetGoalState")
            {
                action = new MudData.FormulaActionSetGoalState();
            }
            else if (ActionComboBox.Text == "SetProperty")
            {
                action = new MudData.FormulaActionSetProperty();
            }
            else if (ActionComboBox.Text == "TriggerEvent")
            {
                action = new MudData.FormulaActionTriggerEvent();
            }
            else
            {
                action = new MudData.FormulaAction();
            }

            return action;
        }

    }
}
