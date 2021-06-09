/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IXMLSerializable
*/

#ifndef IXMLSERIALIZABLE_HPP_
#define IXMLSERIALIZABLE_HPP_

#include <ostream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class IXMLSerializable
{
    public:
        /**
                 * @brief Construct a new IXMLSerializable object
                 * 
                 */
        IXMLSerializable() = default;
        /**
                 * @brief Destroy the IXMLSerializable object
                 * 
                 */
        virtual ~IXMLSerializable() = default;
        /**
                 * @brief Construct a new IXMLSerializable
                 * 
                 * @param other 
                 */
        IXMLSerializable(const IXMLSerializable &other) = delete;
        /**
                 * @brief 
                 * 
                 * @param other 
                 * @return IXMLSerializable& 
                 */
        IXMLSerializable &operator=(const IXMLSerializable &other) = delete;

        virtual std::ostream &operator<<(std::ostream &os) = 0;
        virtual std::istream &operator>>(std::istream &is) = 0;
        virtual boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) = 0;


    protected:
    private:
};

inline std::ostream &operator<<(std::ostream &os, IXMLSerializable &xml)
{
    //xml.SerializeToXML(os);
    return xml.operator<<(os);
}

inline std::istream &operator>>(std::istream &is, IXMLSerializable &xml)
{
    //xml.LoadFromXML(is);
    return xml.operator>>(is);
}

#endif /* !IXMLSERIALIZABLE_HPP_ */