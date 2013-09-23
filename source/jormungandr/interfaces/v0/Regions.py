from flask import Flask
from flask.ext.restful import Resource, fields, marshal_with
from instance_manager import NavitiaManager

region_fields = {
    'region_id': fields.String,
    'status': fields.String,
    'shape': fields.String,
    'start_production_date': fields.String,
    'end_production_date': fields.String
}

regions_fields = {
    'regions' : fields.List(fields.Nested(region_fields))
}


class Regions(Resource):
    @marshal_with(regions_fields)
    def get(self):
        regions = NavitiaManager().regions()
        return regions