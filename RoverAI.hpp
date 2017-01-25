#pragma once

class RoverAI
{

public:

   void run();

   bool isEnabled();

   void setEnabled(
      const bool& enabled);

private:

   bool enabled;
};

inline void RoverAI::run()
{

}

inline bool RoverAI::isEnabled()
{
   return (enabled);
}

inline void RoverAI::setEnabled(
   const bool& enabled)
{
   this->enabled = enabled;
}
