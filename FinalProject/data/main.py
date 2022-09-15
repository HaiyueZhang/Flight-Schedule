# # Dataset Acquisition and Processing 
# The publicly accessible dataset we have chosen to use is [OpenFlights](https://openflights.org/data.html). Due to necessity of reformatting and existence of dirty data, we will implement data cleaning for pre-processing.
#
# ## Data Format
# We plan to use airports data and routes data provided by OpenFlights. After pre-processing, only subsets will be considered for selected data and their information are shown in below two tables.
# - airports data
#
# | Key | Description |
# |---|---|
# | Airport ID | Unique OpenFlights identifier for this airport. |
# | Name | Name of airport. May or may not contain the City name. |
# | City | Main city served by airport. May be spelled differently from Name. |
# | Country | Country or territory where airport is located. See Countries to cross-reference to ISO 3166-1 codes. |
# | Latitude | Decimal degrees, usually to six significant digits. Negative is South, positive is North. |
# | Longitude | Decimal degrees, usually to six significant digits. Negative is West, positive is East. |

import numpy as np
import pandas as pd

col_names = ['Airport ID', 'Name', 'City', 'Country', 'IATA', 'ICAO', 'Latitude', 'Longitude', 'Altitude', 'Timezone', 'DST', 'Tz database time zone', 'Type', 'Source']
airports = pd.read_csv('airports.dat', names = col_names, header = None)
airports = airports.drop(columns = ['IATA', 'ICAO', 'Altitude', 'Timezone', 'DST', 'Tz database time zone', 'Type', 'Source'])

# - routes data
#
# | Key | Description |
# |---|---|
# | Airline | 2-letter (IATA) or 3-letter (ICAO) code of the airline. |
# | Airline ID | Unique OpenFlights identifier for airline (see Airline). |
# | Source airport | 3-letter (IATA) or 4-letter (ICAO) code of the source airport. |
# | Source airport ID | Unique OpenFlights identifier for source airport (see Airport) |
# | Destination airport | 3-letter (IATA) or 4-letter (ICAO) code of the destination airport. |
# | Destination airport ID | Unique OpenFlights identifier for destination airport (see Airport) |
# | Stops | Number of stops on this flight ("0" for direct) |

col_names = ['Airline', 'Airline ID', 'Source airport', 'Source airport ID', 'Destination airport', 'Destination airport ID', 'Codeshare', 'Stops', 'Equipment']
routes = pd.read_csv('routes.dat', names = col_names, header = None)
routes = routes.drop(columns = ['Codeshare', 'Equipment'])

# ## Data Correction
# 1. Transfer the raw data into dataframe and use [Pandas](https://pandas.pydata.org/) package to implement the data wrangling. In Pandas missing data is represented by NaN. Drop entries contaning NaN.
# 2. From the primary key, airport ID, join two data tables. After natural join of two tables, there will not be any missing data.
# 3. Finally, export the corrected data into a new file.
#

# +
# clean NaN
routes = routes[routes['Airline ID'].apply(lambda x: str(x).isdigit())]
routes = routes[routes['Source airport ID'].apply(lambda x: str(x).isdigit())]
routes = routes[routes['Destination airport ID'].apply(lambda x: str(x).isdigit())]

# data type: object -> string -> int
routes['Airline ID'] = routes['Airline ID'].astype(str).astype(int)
routes['Source airport ID'] = routes['Source airport ID'].astype(str).astype(int)
routes['Destination airport ID'] = routes['Destination airport ID'].astype(str).astype(int)

# join tables
routes = routes.merge(airports, left_on='Source airport ID', right_on='Airport ID')
routes = routes.merge(airports, left_on='Destination airport ID', right_on='Airport ID', suffixes=('_1', '_2'))


# -

# ## Distance Between Two Points on Earth
# The dataset contains longitude and latitude data of each airport. With [haversine formula](https://en.wikipedia.org/wiki/Haversine_formula), we can compute [great-circle distance](https://en.wikipedia.org/wiki/Great-circle_distance) (the distance between points on the surface of the earth) between each airport.

def distance(routes):
    # The math module contains a function named radians which converts from degrees to radians.
    lon1 = np.radians(routes['Longitude_1'])
    lon2 = np.radians(routes['Longitude_2'])
    lat1 = np.radians(routes['Latitude_1'])
    lat2 = np.radians(routes['Latitude_2'])

    # Haversine formula
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = np.sin(dlat / 2)**2 + np.cos(lat1) * np.cos(lat2) * np.sin(dlon / 2)**2
    c = 2 * np.arcsin(np.sqrt(a))
    
    # Radius of earth. Use 6371 for kilometers. Use 3956 for miles
    r = 6371
    
    # calculate the result
    return(c * r)


# +
routes['distance'] = distance(routes)
routes.to_csv('input_detail.dat', index = False, header = False)
display(routes)

routes = routes.drop(columns = ['Airline', 'Source airport', 'Source airport ID', 'Destination airport', 'Destination airport ID', 'Stops', 'Name_1', 'City_1', 'Country_1', 'Latitude_1', 'Longitude_1', 'Name_2', 'City_2', 'Country_2', 'Latitude_2', 'Longitude_2'])
routes.to_csv('input.dat', index = False, header = False)
display(routes)
