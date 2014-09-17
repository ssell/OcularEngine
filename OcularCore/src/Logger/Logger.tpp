template<typename T, typename... U>
void Logger::debug(T first, U... args)
{
    m_CurrentMessage.channel = LOGGER_CHANNELS::DEBUG_CHANNEL;
    m_IncompleteMessage.str(std::string());
    m_IncompleteMessage << first;
    log(args...);
}

template<typename T, typename... U>
void Logger::info(T first, U... args)
{
    m_CurrentMessage.channel = LOGGER_CHANNELS::INFO_CHANNEL;
    m_IncompleteMessage.str(std::string());
    m_IncompleteMessage << first;
    log(args...);
}

template<typename T, typename... U>
void Logger::warning(T first, U... args)
{
    m_CurrentMessage.channel = LOGGER_CHANNELS::WARNING_CHANNEL;
    m_IncompleteMessage.str(std::string());
    m_IncompleteMessage << first;
    log(args...);
}

template<typename T, typename... U>
void Logger::error(T first, U... args)
{
    m_CurrentMessage.channel = LOGGER_CHANNELS::ERROR_CHANNEL;
    m_IncompleteMessage.str(std::string());
    m_IncompleteMessage << first;
    log(args...);
}

template<typename T, typename... U>
void Logger::log(T first, U... args)
{
    m_IncompleteMessage << first;
    log(args...);
}