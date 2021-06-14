/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** DelayedPop
*/

#ifndef DELAYEDPOP_HPP_
#define DELAYEDPOP_HPP_

namespace Lua
{
    class State;

    /**
     * @brief Popping variable from Lua Stack at destruction
     * 
     */
    class DelayedPop
    {
        public:
            /**
             * @brief Construct a new Delayed Pop object
             * 
             * @param state 
             * @param nbr 
             */
            DelayedPop(State& state, int nbr);
            /**
             * @brief Destroy the Delayed Pop object
             * 
             */
            ~DelayedPop();
            /**
             * @brief Copy a new Delayed Pop object
             * 
             */
            DelayedPop(const DelayedPop&) = delete;
            /**
             * @brief Assign a new DelayedPop object
             * 
             * @return DelayedPop& asigned DelayedPop
             */
            DelayedPop& operator=(const DelayedPop&) = delete;
        private:
            /**
             * @brief Reference to Lua stack state
             * 
             */
            State& _state;
            /**
             * @brief Number of variable to pop
             * 
             */
            int _nbr;
    };
}

#endif /* !DELAYEDPOP_HPP_ */
