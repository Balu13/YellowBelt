#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    cin >> operation_code;
    
    if (operation_code == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            cin >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    }
    else if (operation_code == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse
{
    vector<string> stop_buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
    if (r.stop_buses.empty())
    {
        cout << "No stop";// << endl;
    }
    else
    {
        for (const string& bus : r.stop_buses)
        {
            cout << bus << " ";
        }
        //cout << endl;
    }
    
    return os;
}

struct StopsForBusResponse
{
    string bus;
    vector<string> bus_stops;
    map<string, vector<string>> *stop_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
    if (r.bus_stops.empty())
    {
        cout << "No bus";// << endl;
    }
    else
    {
        bool isFirst = true;
        for (const string& stop : r.bus_stops)
        {
            if (!isFirst)
                cout << endl;
            isFirst = false;
            cout << "Stop " << stop << ": ";
            if (r.stop_buses->at(stop).size() == 1)
            {
                cout << "no interchange";
            }
            else
            {
                for (const string& other_bus : r.stop_buses->at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        cout << other_bus << " ";
                    }
                }
            }
        }
    }
    
    return os;
}

struct AllBusesResponse
{
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r)
{
    if (r.buses_to_stops.empty())
    {
        cout << "No buses";// << endl;
    }
    else
    {
        bool isFirst = true;
        for (const auto& bus_item : r.buses_to_stops)
        {
            if (!isFirst)
                cout << endl;
            isFirst = false;
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second)
            {
                cout << stop << " ";
            }
        }
    }
    
    return os;
}

class BusManager
{
public:
  void AddBus(const string& bus, const vector<string>& stops)
  {
      vector<string>& bus_stops = buses_to_stops[bus];
      for (const string& stop : stops)
      {
          bus_stops.push_back(stop);
          stops_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const
  {
      BusesForStopResponse response;
      if (!stop.empty())
      {
          if (stops_to_buses.count(stop) > 0)
            response.stop_buses = stops_to_buses.at(stop);
      }

      return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const
  {
      StopsForBusResponse response;
      if (!bus.empty())
      {
          response.bus = bus;
          if (buses_to_stops.count(bus) > 0)
              response.bus_stops = buses_to_stops.at(bus);
          response.stop_buses = pStopBuses;
      }

      return response;
  }

  AllBusesResponse GetAllBuses() const
  {
      AllBusesResponse response;
      response.buses_to_stops = buses_to_stops;

      return response;
  }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
    map<string, vector<string>> *pStopBuses = &stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
