using CellSim.Text;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public class ReadOnlyCliOptions
    {
        protected readonly Dictionary<CliOptionType, CliOption> m_options;
        protected CliOption? m_controllerOption;

        private void EnableOptions(string[] args)
        {
            for (int i = 0; i < args.Length; ++i)
            {
                string arg = args[i];
                bool isMatch = false;
                foreach (var pair in m_options)
                {
                    if (pair.Value.IsMatch(arg))
                    {
                        isMatch = true;
                        if (pair.Value.TakesControl)
                        {
                            if (m_controllerOption != null) {
                                throw new ArgumentException(
                                    CString.Format(
                                        Messages.Get("Cli.CliOptions.m_enableOption.Error.TakesControlError"),
                                        m_controllerOption.Names,
                                        pair.Value.Names
                                    )
                                );
                            }
                            m_controllerOption = pair.Value;
                        }
                        pair.Value.Enable();
                        if (pair.Value.HasValue)
                        {
                            ++i;

                            if (i == args.Length) {
                                throw new ArgumentException($"'{pair.Value.FullName}'{Messages.Get("Cli.CliOptions.m_enableOption.Error.ValueError")}");
                            }

                            pair.Value.AddValue(args[i]);
                        }

                        break;
                    }
                }

                if (!isMatch) {
                    throw new ArgumentException(
                        CString.Format(
                            Messages.Get("Cli.CliOptions.m_enableOption.Error.MatchError"),
                            arg
                        )
                    );
                }
            }
        }

        public ReadOnlyCliOptions(string[] args)
        {
            m_options = new Dictionary<CliOptionType, CliOption>();
            m_controllerOption = null;

            void addOption(CliOption option)
            {
                m_options.Add(option.OptionType, option);
            }

            // ここで、オプションを処理する順番を決めます

            addOption(new BinaryOption());
            addOption(new CsvOption());
            addOption(new ImageOption());
            addOption(new OutputOption());
            addOption(new VideoOption());

            EnableOptions(args);
        }

        public SimulationOption CreateSimulationOption()
        {
            return new SimulationOption(
                m_options[CliOptionType.Binary].IsEnabled,
                m_options[CliOptionType.Csv].IsEnabled,
                m_options[CliOptionType.Image].IsEnabled,
                m_options[CliOptionType.Video].IsEnabled,
                m_options[CliOptionType.Output].Value
            );
        }
    }
}
