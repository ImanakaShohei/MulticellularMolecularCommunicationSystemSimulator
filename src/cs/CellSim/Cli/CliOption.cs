using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public abstract class CliOption : ReadOnlyCliOption
    {
        private bool m_isEnabled;

        public CliOption()
        {
            m_isEnabled = false;
        }

        public bool IsEnabled => m_isEnabled;

        /// <summary>
        /// HasValue()が`true`の時に値を追加する
        /// </summary>
        /// <param name="value">追加する値</param>
        public abstract void AddValue(string value);

        public void Enable()
        {
            if (m_isEnabled && !IsRepeatable)
            {
                throw new InvalidOperationException($"'{Names}'{Messages.Get("Cli.CliOption.Enable.Error")}");
            }

            m_isEnabled = true;
        }

        /// <summary>
        /// オプションが有効な時に呼ばれる関数
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        public abstract void OnActive(
            ReadOnlyCliOptions sender,
            CliOptionActivationArgs args
        );

        /// <summary>
        /// TakesControlが'true'のときに実行される
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        public virtual void Run(ReadOnlyCliOptions sender)
        {
        }
    }
}
