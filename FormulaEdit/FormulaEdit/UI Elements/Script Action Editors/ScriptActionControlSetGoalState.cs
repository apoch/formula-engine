﻿using System;
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
    public partial class ScriptActionControlSetGoalState : UserControl
    {
        internal ScriptActionControlSetGoalState(MudData.FormulaActionSetGoalState action)
        {
            InitializeComponent();

            BindingComboBox.Text = action.binding;
            PropertyComboBox.Text = action.property;
            ValueTextBox.Text = action.value;
        }
    }
}
