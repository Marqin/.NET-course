using System;
using System.Collections.Generic;

namespace XML
{
	[Serializable()]
	public class Przedmiot
	{
		[System.Xml.Serialization.XmlElement("nazwa")]
		public string nazwa;

		[System.Xml.Serialization.XmlElement("ocena")]
		public int ocena;
	}

	[Serializable()]
	public class Student
	{
		[System.Xml.Serialization.XmlElement("name")]
		public string name { get; set; }

		[System.Xml.Serialization.XmlElement("pesel")]
		public string pesel { get; set; }

		[System.Xml.Serialization.XmlElement("adres-zamieszkania")]
		public string adres_zamieszkania { get; set; }

		[System.Xml.Serialization.XmlElement("adres-zameldowania")]
		public string adres_zameldowania { get; set; }

		[System.Xml.Serialization.XmlElement("przedmioty")]
		List<Przedmiot> przedmioty { get; set; }

		[System.Xml.Serialization.XmlElement("uwagi")]
		public string uwagi { get; set; }
	}

	[Serializable()]
	public class Dane
	{
		[System.Xml.Serialization.XmlElement("dane")]
		List<Student> dane;
	}
}

