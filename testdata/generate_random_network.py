#!/usr/bin/env python3
import psycopg2
from shapely.geometry import LineString
from shapely.wkb import dumps as wkbDumps
from random import randint

class Database:
    def __init__(self, dsn):
        self.connection = psycopg2.connect(dsn)

    def createTestNetwork(self, paths):
        with self.connection.cursor() as cursor:
            cursor.execute('DROP TABLE IF EXISTS test_network;')
            cursor.execute('CREATE TABLE test_network ('
                           '    gid bigserial PRIMARY KEY,'
                           '    geom geometry(LineString,21781),'
                           '    path text'
                           ');')
            self.executeMany('INSERT INTO test_network (geom, path) VALUES {}', '(ST_SetSrid(%s, 21781), %s)', cursor, paths)
            self.connection.commit()
            return cursor.rowcount

    def executeMany(self, sql, row, cursor, data):
        values = b','.join(cursor.mogrify(row, r) for r in data)
        cursor.execute(sql.format(values.decode(self.connection.encoding)))


def main():
    db = Database('')
    db.createTestNetwork((wkbDumps(randomOctoLinearLineString(20)),str(i)) for i in range(20))
    print('Test data has been written to "test_network" table.')


start = (683354, 247353)
def randomOctoLinearLineString(steps):
    coords = [start]
    for _ in range(steps):
        coords.append(nextPoint(coords[-1], randint(0,7), randint(0,10)))
    return LineString(coords[1:])


directionFactors = {
    0: (1, 0),
    1: (1, 1),
    2: (0, 1),
    3: (-1, 1),
    4: (-1, 0),
    5: (-1, -1),
    6: (0, -1),
    7: (1, -1)
}
def nextPoint(origin, direction, offset):
    df = directionFactors[direction]
    return tuple(origin[i] + (df[i] * offset * 1000) for i in range(2))

if __name__ == '__main__':
    main()