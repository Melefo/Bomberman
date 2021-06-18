/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IAsset
*/

#ifndef IASSET_HPP_
#define IASSET_HPP_

namespace RayLib
{


    class IAsset {
        public:
            /**
             * @brief Construct a new IAsset object
             * 
             */
            IAsset() = default;
            /**
             * @brief Destroy the IAsset object
             * 
             */
            virtual ~IAsset() = default;
            /**
             * @brief Construct a new IAsset object
             * 
             */
            IAsset(const IAsset&) = delete;
            /**
             * @brief Assignment operator
             * 
             * @return IAsset& 
             */
            IAsset& operator=(const IAsset&) = delete;

        protected:
        private:
    };
}

#endif /* !IASSET_HPP_ */
