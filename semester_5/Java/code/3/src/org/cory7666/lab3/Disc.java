package org.cory7666.lab3;

import com.opencsv.bean.CsvBindByName;

public class Disc implements Comparable<Disc>
{
	@CsvBindByName (column = "Album Title") public final String albumTitle;
	@CsvBindByName (column = "Artist") public final String artist;
	@CsvBindByName (column = "Tracks Count") public final int tracksCount;
	@CsvBindByName (column = "Duration") public final int duration;

	public Disc (String albumTitle, String artist, int tracksCount, int duration)
	{
		this.albumTitle = albumTitle;
		this.artist = artist;
		this.tracksCount = tracksCount;
		this.duration = duration;
	}

	public Disc ()
	{
		this("", "", -1, -1);
	}

	@Override
	public int compareTo (Disc o)
	{
		return albumTitle.length() - o.albumTitle.length();
	}

	@Override
	public String toString ()
	{
		return String.format("Альбом <%s>. Автор <%s>. Песен %d (%d).", albumTitle, artist, tracksCount, duration);
	}
}
