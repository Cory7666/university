from csv import DictReader, DictWriter
from typing import Callable


def correct_value(
    condition: Callable[[str], bool],
    value: str,
    else_value: str,
    then_value: str | None = None
) -> str:
    then_value = then_value if then_value != None else value
    return (
        then_value
        if condition(value.strip().lower())
        else else_value
    )


input_filepath = './2019.csv'
output_filepath = './2019_converted.csv'

required_fields = (
    "Overall rank",
    "Country or region",
    "Score",
    "GDP per capita",
    "Social support",
    "Healthy life expectancy",
    "Freedom to make life choices",
    "Generosity",
    "Perceptions of corruption"
)

new_field_names = (
    "score",
    "gdp_per_capita",
    "social_support",
    "healthy_life_expectancy",
    "freedom_to_make_life_choices",
    "generosity",
    "perceptions_of_corruption"
)

with open(input_filepath, 'r', newline='') as input_file, \
        open(output_filepath, 'w', newline='') as output_file:
    reader = DictReader(input_file)
    writer = DictWriter(output_file, fieldnames=new_field_names)
    writer.writeheader()

    for record in reader:
        writer.writerow(
            {
                new_field_names[0]: correct_value(lambda x: len(x) > 0, record[required_fields[2]], '0'),
                new_field_names[1]: correct_value(lambda x: len(x) > 0, record[required_fields[3]], '0'),
                new_field_names[2]: correct_value(lambda x: len(x) > 0, record[required_fields[4]], '0'),
                new_field_names[3]: correct_value(lambda x: len(x) > 0, record[required_fields[5]], '0'),
                new_field_names[4]: correct_value(lambda x: len(x) > 0, record[required_fields[6]], '0'),
                new_field_names[5]: correct_value(lambda x: len(x) > 0, record[required_fields[7]], '0'),
                new_field_names[6]: correct_value(lambda x: len(x) > 0, record[required_fields[8]], '0'),
            }
        )
