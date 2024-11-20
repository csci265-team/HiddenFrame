/* eslint-disable react/prop-types */

import { Switch as ShadcnSwitch } from "./ui/switch";
import * as SwitchPrimitives from "@radix-ui/react-switch"

type SwitchProps = SwitchPrimitives.SwitchProps & React.RefAttributes<HTMLButtonElement>;

export const Switch: React.FC<SwitchProps> = (props) => {
    return (
        <ShadcnSwitch
            className={`bg-colors-hf-brown text-colors-hf-beige dark:bg-colors-hf-beige dark:text-colors-hf-brown rounded-lg hover:bg-colors-hf-brown/90 dark:hover:bg-colors-hf-beige/90`}
            {...props} />
    );
}