collections_to_resource_type = {
        "stop_points": "stop_point", "routes":"route",
         "networks":"network", "commercial_modes":"commercial_mode",
         "physical_modes":"physical_mode", "companies":"company",
         "stop_areas":"stop_area", "lines":"line",
         "addresses":"address", "coords":"coord",
         "journey_pattern_points" : "journey_pattern_point"}

resource_type_to_collection = {resource_type:collection for collection,
                               resource_type in
                               collections_to_resource_type.iteritems()}