using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace EAPconfig
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public static class ThreadHelperClass
        {
            delegate void SetTextCallback(Form f, Control ctrl, string text);
            /// <summary>
            /// Set text property of various controls
            /// </summary>
            /// <param name="form">The calling form</param>
            /// <param name="ctrl"></param>
            /// <param name="text"></param>
            public static void SetText(Form form, Control ctrl, string text)
            {
                // InvokeRequired required compares the thread ID of the 
                // calling thread to the thread ID of the creating thread. 
                // If these threads are different, it returns true. 
                if (ctrl.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    form.Invoke(d, new object[] { form, ctrl, text });
                }
                else
                {
                    ctrl.Text = ctrl.Text + text;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs b)
        {
            // Get a list of serial port names. 
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();

            //Console.WriteLine("The following serial ports were found:");

            // Display each port name to the console. 
            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
                //Console.WriteLine(port);
            }
        }

        private void button1_Click(object sender, EventArgs b)
        {
            button1.Enabled = false;
            richTextBox1.Text="";

            serialPort1.Close();
            //--------------------------------------------------------------------------------------
            //Ustawienie nazwy portu
            //--------------------------------------------------------------------------------------
            try
            {
                serialPort1.PortName = comboBox1.Text;
            }
            catch { MessageBox.Show("Nie udało się otworzyć portu "); }

            //--------------------------------------------------------------------------------------
            //Ustawienie prędkości połączenia
            //--------------------------------------------------------------------------------------
            serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);

            //--------------------------------------------------------------------------------------
            //Ustawienie bitów parzystości
            //--------------------------------------------------------------------------------------
            if (comboBox3.Text == "Brak")
            {
                serialPort1.Parity = System.IO.Ports.Parity.None;
            }
            else if (comboBox3.Text == "Parzyste")
            {
                serialPort1.Parity = System.IO.Ports.Parity.Even;
            }
            else if (comboBox3.Text == "Nieparzyste")
            {
                serialPort1.Parity = System.IO.Ports.Parity.Odd;
            }
            //--------------------------------------------------------------------------------------
            //Ustawienie ilości bitów stopu
            //--------------------------------------------------------------------------------------
            if (comboBox4.Text == "1")
            {
                serialPort1.StopBits = System.IO.Ports.StopBits.One;
            }
            else if (comboBox4.Text == "2")
            {
                serialPort1.StopBits = System.IO.Ports.StopBits.Two;
            }

            //--------------------------------------------------------------------------------------
            //Zapis parametrów do karty
            //--------------------------------------------------------------------------------------
            string bufor;
            try
            {
                serialPort1.Open();
                bufor = "a\n";
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);
                // Prędkość transmisji
                if (comboBox5.Text == "2400")
                {
                    bufor = "@CONF_BAUD 1\n";
                }
                else if (comboBox5.Text == "4800")
                {
                    bufor = "@CONF_BAUD 2\n";
                }
                else if (comboBox5.Text == "19200")
                {
                    bufor = "@CONF_BAUD 4\n";
                }
                else if (comboBox5.Text == "38400")
                {
                    bufor = "@CONF_BAUD 5\n";
                }
                else if (comboBox5.Text == "57600")
                {
                    bufor = "@CONF_BAUD 6\n";
                }
                else
                {
                    bufor = "@CONF_BAUD 3\n";
                }
                richTextBox1.AppendText(bufor);
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);

                // Parzystość
                if (comboBox6.Text == "Parzyste")
                {
                    bufor = "@CONF_PARITY 2\n";
                }
                else if (comboBox6.Text == "Nieparzyste")
                {
                    bufor = "@CONF_PARITY 1\n";
                }
                else
                {
                    bufor = "@CONF_PARITY 0\n";
                }
                richTextBox1.AppendText(bufor);
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);
                //Bity stopu
                if (comboBox7.Text == "1")
                {
                    bufor = "@CONF_STOPBITS 1\n";
                }
                else
                {
                    bufor = "@CONF_STOPBITS 2\n";
                }
                richTextBox1.AppendText(bufor);
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);

                //TCP mode
                if(checkBox1.Checked)
                    bufor = "@CONF_TCP_MODE 1\n";
                else
                    bufor = "@CONF_TCP_MODE 0\n";
                richTextBox1.AppendText(bufor);
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);
            }
            catch
            {
                MessageBox.Show("Nie udało się otworzyć portu " + comboBox1.Text);
            }
            button1.Enabled = true;
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            ThreadHelperClass.SetText(this, richTextBox1, serialPort1.ReadExisting()); 
        }

        private void Form1_Leave(object sender, EventArgs b)
        {
            serialPort1.Close();
        }

        private void button2_Click(object sender, EventArgs b)
        {
            button2.Enabled = false;
            richTextBox1.Text = "";

            serialPort1.Close();
            //--------------------------------------------------------------------------------------
            //Ustawienie nazwy portu
            //--------------------------------------------------------------------------------------
            try
            {
                serialPort1.PortName = comboBox1.Text;
            }
            catch { MessageBox.Show("Nie udało się otworzyć portu "); }
            //--------------------------------------------------------------------------------------
            //Ustawienie prędkości połączenia
            //--------------------------------------------------------------------------------------
            serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);

            //--------------------------------------------------------------------------------------
            //Ustawienie bitów parzystości
            //--------------------------------------------------------------------------------------
            if (comboBox3.Text == "Brak")
            {
                serialPort1.Parity = System.IO.Ports.Parity.None;
            }
            else if (comboBox3.Text == "Parzyste")
            {
                serialPort1.Parity = System.IO.Ports.Parity.Even;
            }
            else if (comboBox3.Text == "Nieparzyste")
            {
                serialPort1.Parity = System.IO.Ports.Parity.Odd;
            }
            //--------------------------------------------------------------------------------------
            //Ustawienie ilości bitów stopu
            //--------------------------------------------------------------------------------------
            if (comboBox4.Text == "1")
            {
                serialPort1.StopBits = System.IO.Ports.StopBits.One;
            }
            else if (comboBox4.Text == "2")
            {
                serialPort1.StopBits = System.IO.Ports.StopBits.Two;
            }

            //--------------------------------------------------------------------------------------
            //Zapis parametrów do karty
            //--------------------------------------------------------------------------------------
            string bufor;
            byte[]  buforByte = new byte[20];
            try
            {
                serialPort1.Open();
                bufor = "a\n";
                serialPort1.Write(bufor);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);
                //Adres karty
                bufor = "@CONF_ADDR " + System.Convert.ToChar(System.Convert.ToByte(System.Convert.ToUInt16(numericUpDown1.Value))) + "\n";

                for (int i = 0; i < bufor.Length; i++)
                { 
                    buforByte[i]=System.Convert.ToByte(bufor[i]);
                }
                richTextBox1.AppendText(bufor);
                //serialPort1.Write(bufor);
                serialPort1.Write(buforByte, 0, bufor.Length);
                for (int i = 0; i < 20; i++)
                    System.Threading.Thread.Sleep(1);
                for (int i = 0; i < bufor.Length; i++)
                {
                    buforByte[i] = 0;
                }
            }
            catch 
            {
                MessageBox.Show("Nie udało się otworzyć portu " + comboBox1.Text);
            }
            button2.Enabled = true;
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
