

class Command{

  void Command(std::string commandName){_commandName = commandName;}
  
  virtual bool operation();

  private:
    std::string _commandName;
    






};
