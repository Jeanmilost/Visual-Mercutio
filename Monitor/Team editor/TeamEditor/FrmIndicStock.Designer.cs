namespace TeamEditor
{
    partial class FrmIndicStock
    {
        /// <summary>
        /// Required designer variable
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmIndicStock));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cboProc = new System.Windows.Forms.ComboBox();
            this.cmdQuery = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.cboAnnee = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboModel = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.grdPreview = new System.Windows.Forms.DataGridView();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grdPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.cboProc);
            this.groupBox1.Controls.Add(this.cmdQuery);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cboAnnee);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cboModel);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(531, 132);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "S�lection";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "Processus :";
            // 
            // cboProc
            // 
            this.cboProc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboProc.FormattingEnabled = true;
            this.cboProc.Location = new System.Drawing.Point(125, 85);
            this.cboProc.Name = "cboProc";
            this.cboProc.Size = new System.Drawing.Size(283, 21);
            this.cboProc.TabIndex = 13;
            // 
            // cmdQuery
            // 
            this.cmdQuery.Location = new System.Drawing.Point(427, 83);
            this.cmdQuery.Name = "cmdQuery";
            this.cmdQuery.Size = new System.Drawing.Size(75, 23);
            this.cmdQuery.TabIndex = 12;
            this.cmdQuery.Text = "G�n�ration";
            this.cmdQuery.UseVisualStyleBackColor = true;
            this.cmdQuery.Click += new System.EventHandler(this.cmdQuery_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Ann�e :";
            // 
            // cboAnnee
            // 
            this.cboAnnee.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboAnnee.FormattingEnabled = true;
            this.cboAnnee.Location = new System.Drawing.Point(125, 56);
            this.cboAnnee.Name = "cboAnnee";
            this.cboAnnee.Size = new System.Drawing.Size(107, 21);
            this.cboAnnee.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Model Ref :";
            // 
            // cboModel
            // 
            this.cboModel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboModel.FormattingEnabled = true;
            this.cboModel.Location = new System.Drawing.Point(125, 29);
            this.cboModel.Name = "cboModel";
            this.cboModel.Size = new System.Drawing.Size(202, 21);
            this.cboModel.TabIndex = 6;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.grdPreview);
            this.groupBox2.Location = new System.Drawing.Point(12, 150);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(531, 387);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Pr�visualisation des r�sultats";
            // 
            // grdPreview
            // 
            this.grdPreview.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdPreview.Location = new System.Drawing.Point(6, 19);
            this.grdPreview.Name = "grdPreview";
            this.grdPreview.Size = new System.Drawing.Size(519, 362);
            this.grdPreview.TabIndex = 0;
            // 
            // FrmIndicStock
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(552, 549);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FrmIndicStock";
            this.Text = "Indicateur �tat du stock annuel des traitements � effectuer";
            this.Load += new System.EventHandler(this.FrmIndicStock_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grdPreview)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cboAnnee;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboModel;
        private System.Windows.Forms.Button cmdQuery;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView grdPreview;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboProc;

    }
}