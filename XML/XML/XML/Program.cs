using System;
using System.Xml.Schema;
using System.Xml.Linq;
using System.Xml;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Text.RegularExpressions;

namespace XML
{
	class MainClass
	{
		static string XMLdata = "<dane>\n<student>\n<name>Jan Jan</name>\n<pesel>444</pesel>\n<adres-zamieszkania>Stawowa 1</adres-zamieszkania>\n<adres-zameldowania>Jelenia 2</adres-zameldowania>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>6a</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n<student>\n<name>Jan Nowal</name>\n<pesel>123</pesel>\n<adres-zamieszkania>Stawowa 2</adres-zamieszkania>\n<adres-zameldowania>Jelenia 1</adres-zameldowania>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>5</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n<student>\n<name>Jan Kowalski</name>\n<pesel>456</pesel>\n<adres-zamieszkania>Ulicowa 3</adres-zamieszkania>\n<adres-zameldowania>Ulicowa 3</adres-zameldowania>\n<uwagi>bla bla</uwagi>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>4</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n</dane>";
		static string validXMLdata = "<dane>\n<student>\n<name>Jan Jan</name>\n<pesel>444</pesel>\n<adres-zamieszkania>Stawowa 1</adres-zamieszkania>\n<adres-zameldowania>Jelenia 2</adres-zameldowania>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>6</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n<student>\n<name>Jan Nowal</name>\n<pesel>123</pesel>\n<adres-zamieszkania>Stawowa 2</adres-zamieszkania>\n<adres-zameldowania>Jelenia 1</adres-zameldowania>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>5</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n<student>\n<name>Jan Kowalski</name>\n<pesel>456</pesel>\n<adres-zamieszkania>Ulicowa 3</adres-zamieszkania>\n<adres-zameldowania>Ulicowa 3</adres-zameldowania>\n<uwagi>bla bla</uwagi>\n<przedmioty>\n\t<przedmiot>\n\t<nazwa>polski</nazwa>\n\t<ocena>4</ocena>\n\t</przedmiot>\n</przedmioty>\n</student>\n</dane>";
		static string XMLschema = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" elementFormDefault=\"qualified\" attributeFormDefault=\"unqualified\">\n       <xs:element name=\"dane\">\n              <xs:complexType>\n                     <xs:sequence>\n                            <xs:element name=\"student\" maxOccurs=\"unbounded\">\n                                   <xs:complexType>\n                                          <xs:sequence>\n                                                 <xs:element name=\"name\" type=\"xs:string\"></xs:element>\n                                                 <xs:element name=\"pesel\" type=\"xs:string\"></xs:element>\n                                                 <xs:element name=\"adres-zamieszkania\" type=\"xs:string\"></xs:element>\n                                                 <xs:element name=\"adres-zameldowania\" type=\"xs:string\"></xs:element>\n                                                 <xs:element type=\"xs:string\" name=\"uwagi\" minOccurs=\"0\"/>\n                                                 <xs:element name=\"przedmioty\">\n                                                        <xs:complexType>\n                                                               <xs:sequence>\n                                                                      <xs:element name=\"przedmiot\">\n                                                                             <xs:complexType>\n                                                                                    <xs:sequence>\n                                                                                           <xs:element name=\"nazwa\" type=\"xs:string\"></xs:element>\n                                                                                           <xs:element name=\"ocena\" type=\"xs:int\"></xs:element>\n                                                                                       </xs:sequence>\n                                                                                </xs:complexType>\n                                                                         </xs:element>\n                                                                  </xs:sequence>\n                                                           </xs:complexType>\n                                                    </xs:element>\n                                             </xs:sequence>\n                                      </xs:complexType>\n                               </xs:element>\n                        </xs:sequence>\n                 </xs:complexType>\n          </xs:element>\n   </xs:schema>\n\n";

		public static void Main (string[] args)
		{
			XmlSchemaSet schemas = new XmlSchemaSet();
			schemas.Add ("", XmlReader.Create(new StringReader(XMLschema)));
			XDocument doc = XDocument.Parse (XMLdata);
			doc.Validate(schemas, (o, e) =>
				{
					Console.WriteLine("{0}", e.Message);
				});
		

			XmlReaderSettings settings = new XmlReaderSettings();
			settings.Schemas.Add ("", XmlReader.Create(new StringReader(XMLschema)));
			settings.ValidationType = ValidationType.Schema;
			XmlReader reader = XmlReader.Create(new StringReader(XMLdata), settings);
			XmlDocument document = new XmlDocument();
			try{
				document.Load(reader);
			} catch ( XmlSchemaValidationException e ) {
				System.Console.WriteLine ("{0}", e.Message);
			}



			var regex = new Regex("\\sK[A-z]+$");

			XDocument xdoc = XDocument.Parse (validXMLdata);
			
			var tests =
				from el in xdoc.Element("dane").Elements("student")
					where regex.IsMatch(el.Element("name").Value)
				select el;

			foreach (XElement el in tests)
				Console.WriteLine ((string)el.Element("name"));


	
		}


	}
}
