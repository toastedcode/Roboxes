#pragma once

class FollowAI
{

public:

   void run();

   bool isEnabled();

   void setEnabled(
      const bool& enabled);

private:

   bool enabled;
};

inline void FollowAI::run()
{

}

inline bool FollowAI::isEnabled()
{
   return (enabled);
}

inline void FollowAI::setEnabled(
   const bool& enabled)
{
   this->enabled = enabled;
}
